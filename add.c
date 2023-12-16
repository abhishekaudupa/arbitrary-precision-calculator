#include "add.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

Number *add(Number *const operand1, Number *const operand2) {
    //design time check
    assert(operand1 && operand2);

    //get traversers to both numbers.
    Digit_Node *trav1 = NULL;
    Digit_Node *trav2 = NULL;

    //return pointer.
    Number *to_ret = NULL;

    //if we're adding numbers without a decimal dot
    if((operand1->tail->distance_from_dot < 0)
	    && (operand2->tail->distance_from_dot < 0)) {
	trav1 = operand1->tail;
	trav2 = operand2->tail;
	to_ret = operand2;
    } else {		//otherwise
	//set trav2 to the number which has the farthest digit from decimal dot.
	if(operand1->tail->distance_from_dot > operand2->tail->distance_from_dot) {
	    trav2 = operand1->tail;
	    trav1 = operand2->tail;
	    to_ret = operand1;
	} else {
	    trav2 = operand2->tail;
	    trav1 = operand1->tail;
	    to_ret = operand2;
	}
	
	//ensure traversers are pointing to digits at same decimal place.
	while(trav1->distance_from_dot > trav2->distance_from_dot)
	    trav1 = trav1->prev;

	while(trav2->distance_from_dot > trav1->distance_from_dot)
	    trav2 = trav2->prev;
    }

    //to keep track of carry.    
    unsigned char carry = 0;

    //traverse digits and add
    while(trav1 && trav2) {

	//skip decimal dot.
	if(trav1->digit == '.') {
	    //decrement traversers.
	    trav1 = trav1->prev;
	    trav2 = trav2->prev;
	    continue;
	}

	//calculate the sum of digits.
	unsigned char sum = trav1->digit + trav2->digit + carry;
	carry = 0;

	//check if sum generates carry.
	if(sum > 9) {
	    carry = 1;
	    sum = sum % 10;
	}

	//set the sum to trav2's digit.
	trav2->digit = sum;

	//decrement traversers.
	trav1 = trav1->prev;
	trav2 = trav2->prev;
    }

    //add left over digits of trav2.
    while(trav2) {

	//calculate the sum of digits.
	unsigned char sum = trav2->digit + carry;
	carry = 0;

	//check if sum generates carry.
	if(sum > 9) {
	    carry = 1;
	    sum = sum % 10;
	}

	//set the sum to trav2's digit.
	trav2->digit = sum;

	//decrement traversers.
	trav2 = trav2->prev;
    }

    //add left over digits of trav1.
    while(trav1) {

	//calculate the sum of digits.
	unsigned char sum = trav1->digit + carry;
	carry = 0;

	//check if sum generates carry.
	if(sum > 9) {
	    carry = 1;
	    sum = sum % 10;
	}

	//insert the digit as MSD of trav2.
	insert_at_first(sum + '0', &(to_ret->head));

	//decrement traversers.
	trav1 = trav1->prev;
    }

    //if there's a carry, add it.
    if(carry)
	insert_at_first(carry + '0', &(to_ret->head));

    return to_ret;
}
