#include <assert.h>
#include <stddef.h>
#include "operation.h"
#include "add.h"
#include "subtract.h"

Number *resolve(Number *const num1, Number *const num2, const char oprtr) {
    //design time check
    assert(num1 && num2);
    assert(oprtr == '+' 
	    || oprtr == '-'
	    || oprtr == 'x'
	    || oprtr == 'X'
	    || oprtr == '/');

    //if addition is requested.
    if(oprtr == '+') {

	//check if both numbers have same sign.
	if(num1->sign == num2->sign) {
	    //simply add 'em.
	    return add(num1, num2);
	} else {
	    //subtract 'em.

	    //determine the number of greater magnitude.
	    if(abs_greater_than(num1, num2)) {
		//subtract num2 from num1.
		return subtract(num1, num2);
	    } else {
		//subtract num1 from num2.
		return subtract(num2, num1);
	    }
	}
    }

    //if subtraction is requested.
    if(oprtr == '-') {

	//convert subtraction request to addition request.
	if(num2->sign == '+')
	    num2->sign = '-';
	else
	    num2->sign = '+';

	//add 'em via recursive call.
	return resolve(num1, num2, '+');
    }

    //if multiplication is requested.
    if(oprtr == 'x' || oprtr == 'X') {
	//TBD.
	return num1;
    }

    //finally, if division is requested. TBD.
    return num1;
}
