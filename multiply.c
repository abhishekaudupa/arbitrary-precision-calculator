#include "multiply.h"
#include "stddef.h"
#include <assert.h>
#include <stdio.h>
#include "allocator.h"

Number *multiply(Number *const operand1, Number *const operand2) {
    //design time check
    assert(operand1 && operand2);

    //return variable.
    Number *product = get_memory(sizeof(*product));

    //init
    product->head = product->tail = NULL;
    product->sign = '+';
    
    //get digit lengths
    unsigned int dl1 = get_digit_count(operand1);
    unsigned int dl2 = get_digit_count(operand2);

    //get traversers to tail both numbers.
    Digit_Node *trav1 = NULL;
    Digit_Node *trav2 = NULL;

    //trav2 for number with least digits.
    if(dl1 > dl2) {
	trav1 = operand1->tail;
	trav2 = operand2->tail;
    } else {
	trav2 = operand1->tail;
	trav1 = operand2->tail;
    }

    //start multiplication.

    //to track carry.
    unsigned char carry = 0;

    //traverser start position for product's digits (decremnted each iteration).
    Digit_Node **trav3 = &(product->tail);

    //traverse each of trav2 digits.
    while(trav2) {

	//skip decimal dot.
	if(trav2->digit == '.') {
	    trav2 = trav2->prev;
	    continue;
	}

	//traverser for multiplicand.
	Digit_Node *trav1_r = trav1;

	//traverser for product.
	Digit_Node *trav_p = *trav3;

	//multiply with each of trav1's digits.
	while(trav1_r) {

	    //skip decimal dot.
	    if(trav1_r->digit == '.') {
		trav1_r = trav1_r->prev;
		continue;
	    }

	    //calculate digit.
	    unsigned char digit_prod = (trav2->digit) * (trav1_r->digit) + carry;

	    //if we have already multiplied trav2's lsd.
	    if(trav_p)
		digit_prod += trav_p->digit;

	    //clear carry.
	    carry = 0;

	    //check if carry is generated.
	    if(digit_prod > 9) {
		carry = digit_prod / 10;
		digit_prod = digit_prod % 10;
	    }

	    //build product.
	    if(trav_p) {
		//add to the existing digit.
		trav_p->digit = digit_prod;

		//shift trav_p left.
		trav_p = trav_p->prev;
	    } else {
		insert_at_first(digit_prod + '0', product);
	    }

	    //shift trav1_r left.
	    trav1_r = trav1_r->prev;
	}

	//if there's a carry, prepend it.
	if(carry) {
	    insert_at_first(carry + '0', product);
	    carry = 0;
	}

	//shift trav2 left.
	trav2 = trav2->prev;

	//shift trav3 left.
	trav3 = &((*trav3)->prev);
    }

    //assign place values to digits of product.
    assign_place_value(product);

    /* we need to check if the operand/s were fractions and divide
       the product accordingly */

    //10's power by which to change the magnitude.
    int magnitude_delta = 0;

    //if operand1 is a fraction.
    if(operand1->tail->distance_from_dot > 0)
	magnitude_delta += operand1->tail->distance_from_dot;

    //if operand2 is a fraction.
    if(operand2->tail->distance_from_dot > 0)
	magnitude_delta += operand2->tail->distance_from_dot;

    //reduce order of magnitude of product.
    modify_order_of_magnitude(product, -magnitude_delta);

    //set the sign of the product.
    if((operand1->sign == '+' && operand2->sign == '-')
	    || (operand1->sign == '-' && operand2->sign == '+'))
	product->sign = '-';

    return product;
}
