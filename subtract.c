#include "subtract.h"
#include <assert.h>

/*
   Function to subtract operand2 from operand1 and return operand1.
 */
Number *subtract(Number *const operand1, Number *const operand2) {

    //design time check.
    assert(operand1 && operand2);

    /* Implicit Assumption: |operand1| >= |operand2|.
       We'll only subtract operand2 from operand1.
     */

    //get digit traversers for both numbers.
    Digit_Node *trav1 = operand1->tail;
    Digit_Node *trav2 = operand2->tail;

    //see if operand1 needs a decimal dot.
    if(trav1->distance_from_dot < 0 && trav2->distance_from_dot > 0) {
	//append '.0' to operand1
	insert_at_last('.', operand1);
	insert_at_last('0', operand1);

	//reassign place values.
	assign_place_value(operand1);

	//reset trav1.
	trav1 = operand1->tail;
    }

    //if operand1 has more digits after decimal dot than operand1
    while(trav1->distance_from_dot > trav2->distance_from_dot)
	trav1 = trav1->prev;

    //if operand2 has more digits after decimal dot than operand1
    if(trav2->distance_from_dot > trav1->distance_from_dot) {

	//append requisite zeroes to operand1.
	for(int i = 0; i < (trav2->distance_from_dot - trav1->distance_from_dot); ++i)
	    insert_at_last('0', operand1);

	//reset trav1.
	trav1 = operand1->tail;
    }

    //now we're subtracting digits at same decimal place.

    //we'll traverse digits and subtract.
    while(trav1 && trav2) {

	//skip decimal dot.
	if(trav1->digit == '.') {
	    //traverse left.
	    trav1 = trav1->prev;
	    trav2 = trav2->prev;
	}

	//check if digit1 >= digit2.
	if(trav1->digit >= trav2->digit) {
	    //subtract and store.
	    trav1->digit = trav1->digit - trav2->digit;
	} else {
	    //we'll have to borrow from left.

	    //get a borrow traverser.
	    Digit_Node *borr_trav = trav1->prev;

	    //traverse left for borrowing.
	    while(borr_trav->digit == 0 || borr_trav->digit == '.') {
		borr_trav = borr_trav->prev;
	    }

	    //traverse back with borrow.
	    while(borr_trav != trav1) {
		//shift borrow traverser to right.
		borr_trav = borr_trav->next;

		//skip decimal dot.
		if(borr_trav->digit == '.')
		    continue;

		//borrow digit is incremented by 10.
		borr_trav->digit += 10;

		//previous digit decremented (ensure it's a digit).
		if(borr_trav->prev->digit != '.')
		    --(borr_trav->prev->digit);
		else
		    --(borr_trav->prev->prev->digit);
	    }

	    //subtract and store.
	    trav1->digit = trav1->digit - trav2->digit;
	}

	//traverse left.
	trav1 = trav1->prev;
	trav2 = trav2->prev;
    }

    //remove redundant zeros in operand 1.
    sanitize(operand1);

    return operand1;
}
