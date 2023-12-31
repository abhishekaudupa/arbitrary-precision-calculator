#include "divide.h"
#include <assert.h>
#include <stddef.h>
#include "subtract.h"
#include <stdio.h>
#include "allocator.h"

/*
   Function to divide operand1 by operand2.
 */
Number *divide(Number *const operand1, Number *const operand2) {
    //design time check.
    assert(operand1 && operand2);

    //get a quotient variable.
    Number *quotient = get_memory(sizeof(*quotient));

    //init
    quotient->head = quotient->tail = NULL;
    quotient->sign = '+';

    /* We'll be dividing whole numbers only. For that we'll convert
       numbers with fractional parts to whole numbers by multiplying 
       by powers 10. Also we'll make operand1 greater than operand2, 
       if it already isn't and keep note of the multiplication factor.

       We'll finally divide the quotient by the multiplication factor. */

    //convert operands to whole numbers and store multiplying factors.
    int factor1 = make_whole(operand1);
    int factor2 = make_whole(operand2);

    //if operand1 is of greater magnitude.
    while(abs_greater_than(operand1, operand2)) {
	//make operand2 bigger
	modify_order_of_magnitude(operand2, 1);
	++factor2;
    }

    //if operand2 is of greater magnitude.
    while(abs_greater_than(operand2, operand1)) {
	//make operand1 bigger
	modify_order_of_magnitude(operand1, 1);
	++factor1;
    }

    //now operand1 is exactly one order of magnitude bigger than operand2.

    //to store quotient during each division pass.
    char quotient_digit = 0;

    //to keep track of the decimal place during division (if any).
    int quotient_factor = 0;

    //1st division pass (before generating decimal point).
    while(!abs_greater_than(operand2, operand1)) {
	subtract(operand1, operand2);
	++quotient_digit;
    }

    //build the quotient number's digit before decimal.
    insert_at_last(quotient_digit + '0', quotient);

    //update place values of digits.
    assign_place_value(quotient);

    //operand1 is the remainder at this point.

    //decimal point generation, if necessary.
    if(!is_zero(operand1)) {
	if(abs_greater_than(operand2, operand1)) {
	    modify_order_of_magnitude(operand1, 1);
	}
    }

    //continue subsequent divisions, if necessary.
    while(!is_zero(operand1) && quotient_factor < MAX_DIGIT_PRECISION) {
	//divide.
	quotient_digit = 0;
	while(!abs_greater_than(operand2, operand1)) {
	    subtract(operand1, operand2);
	    ++quotient_digit;
	}

	//append the quotient digit to the quotient.
	insert_at_last(quotient_digit + '0', quotient);

	//update place values of digits.
	assign_place_value(quotient);

	//multiply remainder by 10 if necessary.
	if(abs_greater_than(operand2, operand1)) {
	    modify_order_of_magnitude(operand1, 1);
	    ++quotient_factor;
	}
    }

    //adjust magnitude of the quotient.
    modify_order_of_magnitude(quotient, factor2 - factor1 - quotient_factor);

    //set the sign of the quotient.
    if((operand1->sign == '+' && operand2->sign == '-')
	    || (operand1->sign == '-' && operand2->sign == '+'))
	quotient->sign = '-';

    return quotient;
}
