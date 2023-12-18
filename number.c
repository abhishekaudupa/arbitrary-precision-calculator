#include "number.h"
#include "argument.h"
#include "allocator.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

Number get_number(const char *const number_string) {

    //design time verification.
    assert(number_string);

    //get a string traverser variable.
    size_t i = 0;

    //get a string limit index variable.
    size_t j = strlen(number_string) - 1;

    //return variable.
    Number number = { NULL, NULL, '+' };

    //check for explicit sign of the number.
    if(is_sign(number_string[0])) {
	number.sign = number_string[0];
	++i;
    }

    //disregard redundant zeroes in operand.
    while(i < j) {
	//disregard preceding zeroes.
	if(number_string[i] == '0') {
	    ++i;
	    continue;
	}
	
	//if you encounter a decimal dot.
	if(number_string[i] == '.') {
	    
	    //number is less than 1 in magnitude.
	    insert_at_last('0', &number);

	    //disregard redudant zeroes, if any, after dot.
	    while(j > i) {
		if(number_string[j] == '0' || number_string[j] == '.')
		    --j;
		else
		    break;
	    }

	    //exit loop.
	    break;
	} else {
	    //stop otherwise.
	    break;
	}
    }

    //traverse the number string.
    while(i <= j) {
	//insert the digit at the last node.
	insert_at_last(number_string[i], &number);
	++i;
    }

    //assign place values to digits.
    assign_place_value(&number);

    return number;
}

Status insert_at_last(const char digit, Number *const number) {

    //design time verification.
    assert(number);
    assert((digit >= '0' && digit <= '9') || digit == '.');

    //get memory for a new digit.
    Digit_Node *new = get_memory(sizeof(*new));

    //if allocation fails.
    if(!new)
	return s_failure;

    //set the digit
    new->digit = (digit == '.')? digit: digit - '0';

    //check if the list is empty
    if(!(number->head)) {

	//set head and tail.
	number->head = number->tail = new;

	//set links
	new->prev = NULL;
	new->next = NULL;

	return s_success;
    }

    //if list isn't empty, go below.

    //set new after tail.
    number->tail->next = new;

    //set new's links.
    new->next = NULL;
    new->prev = number->tail;

    //increment tail.
    number->tail = new;

    return s_success;
}

void print_number(const Number *const number) {

    //design time check.
    assert(number);

    //get a traverser for digits.
    Digit_Node *trav = number->head;

    //print the sign
    if(number->sign == '-')
	fprintf(stdout, "%c", number->sign);

    //ignore preceding zeroes.
    while(trav) {

	//check if digit is zero.
	if(trav->digit == 0) {
	    //check if next digit is a decimal dot.
	    if(trav->next) {
		if(trav->next->digit == '.') {
		    //print zero
		    fprintf(stdout, "%hhu", trav->digit);

		    //incr. traverser.
		    trav = trav->next;

		    break;
		}
	    } else {
		//the number is zero.
		fprintf(stdout, "%hhu", trav->digit);
	    }
	} else {
	    //break if digit not zero.
	    break;
	}

	//increment traverser.
	trav = trav->next;
    }

    //traverse list and print digits.
    while(trav) {

	if(trav->digit == '.') {
	    //print the decimal dot.
	    fprintf(stdout, "%c", trav->digit);
	} else {
	    //print the digit.
	    fprintf(stdout, "%hhu", trav->digit);
	}

	//increment traverser.
	trav = trav->next;
    }
}

void assign_place_value(const Number *const number) {

    //design time check.
    assert(number);

    //get a traverser.
    Digit_Node *trav = number->head;

    //traverse till decimal point/end.
    while(trav->next) {

	//detect decimal point.
	if(trav->digit == '.') {
	    //set the dot's place as zero.
	    trav->distance_from_dot = 0;

	    //get another traverser.
	    Digit_Node *trav_n = trav->next;

	    //decrement current traverser.
	    trav = trav->prev;

	    //set place values before dot.
	    while(trav) {

		//set place value.
		trav->distance_from_dot = trav->next->distance_from_dot - 1;

		//decrement traverser.
		trav = trav->prev;
	    }

	    //set place values after dot.
	    while(trav_n) {

		//set place value.
		trav_n->distance_from_dot = trav_n->prev->distance_from_dot + 1;

		//decrement traverser.
		trav_n = trav_n->next;
	    }

	    return;
	}

	//increment traverser.
	trav = trav->next;
    }

    //we're here: decimal point not found.

    //set place values.
    trav->distance_from_dot = -1;

    //decrement traverser.
    trav = trav->prev;

    //traverse to beginning.
    while(trav) {

	//set place value.
	trav->distance_from_dot = trav->next->distance_from_dot - 1;

	//decrement traverser.
	trav = trav->prev;
    }
}

/* Function to check if num1 > num2 */
Bool_t abs_greater_than(const Number *const num1, const Number *const num2) {

    //design time check.
    assert(num1 && num2);

    //check place value of most sig. digit.
    if(num1->head->distance_from_dot < num2->head->distance_from_dot) {
	//num1 is greater.
	return b_true;
    }

    if(num1->head->distance_from_dot > num2->head->distance_from_dot) {
	//num2 is greater.
	return b_false;
    }

    //both numbers are of same order of magnitude. Go below.

    //get traversers to traverse digits
    Digit_Node *trav1 = num1->head;
    Digit_Node *trav2 = num2->head;

    //compare digit by digit.
    while(trav1 && trav2) {

	//compare digits
	if(trav1->digit > trav2->digit) {
	    //num1 is greater.
	    return b_true;
	}

	if(trav1->digit < trav2->digit) {
	    //num2 is greater.
	    return b_false;
	}

	//increment traversers.
	trav1 = trav1->next;
	trav2 = trav2->next;
    }

    //compare leftover digits on num1.
    while(trav1) {
	//check if digit is not zero.
	if(trav1->digit != '.') {
	    if(trav1->digit) {
		//num1 is greater.
		return b_true;
	    }
	}

	//increment traverser.
	trav1 = trav1->next;
    }

    //num1 is not greater.
    return b_false;
}

Status insert_at_first(const char digit, Number *const number) {

    //design time verification.
    assert(number);
    assert((digit >= '0' && digit <= '9') || digit == '.');

    //get memory for a new digit.
    Digit_Node *new = get_memory(sizeof(*new));

    //if allocation fails.
    if(!new)
	return s_failure;

    //set the digit
    new->digit = (digit == '.')? digit: digit - '0';

    //set new's links.
    new->next = number->head;
    new->prev = NULL;

    //check if number is empty.
    if(!(number->head)) {
	number->head = number->tail = new;
	return s_success;
    }

    //continue otherwise.

    //set new before head.
    (number->head)->prev = new;

    //decrement head.
    number->head = new;

    return s_success;
}

unsigned int get_digit_count(const Number *const number) {
    //design time check.
    assert(number);

    //return digit count for number with decimal dot.
    if(number->tail->distance_from_dot > 0)
	return number->tail->distance_from_dot - number->head->distance_from_dot;

    //return digit count for number without decimal dot.
    return number->tail->distance_from_dot - number->head->distance_from_dot + 1;
}

/* Function to multiply or divide by 10 aka change of magnitude */
Status modify_order_of_magnitude(Number *const number, int magnitude_delta) {
    //design time check.
    assert(number);
    assert(number->head);
    assert(number->tail);

    //no change in number's magnitude.
    if(!magnitude_delta)
	return s_success;

    //if number has no decimal dot.
    if(number->tail->distance_from_dot < 0) {

	//check if change is positive (multiplying).
	if(magnitude_delta > 0) {
	    //append zeroes.
	    for(int i = 0; i < magnitude_delta; ++i)
		insert_at_last('0', number);
	    return s_success;
	} else {	//dividing.

	    //if we have to shift the dot beyond the msd.
	    if(magnitude_delta <= number->head->distance_from_dot) {

		//prepend requisite number of zeroes after decimal dot and before MSD.
		int zeroes_to_prepend = -magnitude_delta + number->head->distance_from_dot;
		for(int i = 0; i < zeroes_to_prepend; ++i) {
		    insert_at_first('0', number);
		}

		//prepend a '0.'
		insert_at_first('.', number);
		insert_at_first('0', number);
		return s_success;
	    }

	    //otherwise.

	    //traverse steps back from tail.
	    Digit_Node *trav = number->tail;
	    for(int i = 0; i < -magnitude_delta; ++i)
		trav = trav->prev;

	    //insert a decimal dot after trav.
	    return insert_after('.', trav);
	}
    }

    //number has a decimal dot.

    //get a traverser.
    Digit_Node *trav = number->head;

    //traverse to dot.
    while(trav) {
	if(trav->digit == '.')
	    break;
	trav = trav->next;
    }

    //multiply
    if(magnitude_delta > 0) {

	//shfit dot right
	for(int i = 0; i < magnitude_delta; ++i) {
	    trav->digit = trav->next->digit;
	    trav->next->digit = '.';
	    if(!(trav->next->next))
		insert_at_last('0', number);
	    trav = trav->next;
	}
    } else {	//divide

	//shift dot left.
	for(int i = 0; i < -magnitude_delta; ++i) {
	    trav->digit = trav->prev->digit;
	    trav->prev->digit = '.';
	    if(!(trav->prev->prev))
		insert_at_first('0', number);
	    trav = trav->prev;
	}
    }

    return s_success;
}

Status insert_after(const char digit_to_insert, Digit_Node *const digit) {
    //design time check.
    assert(digit);
    assert(digit_to_insert == '.');

    //allocate memory.
    Digit_Node *new_dot = get_memory(sizeof(*new_dot));

    if(!new_dot)
	return s_failure;

    //set data
    new_dot->digit = digit_to_insert;

    //set new's next.
    new_dot->next = digit->next;

    //relink digit.
    digit->next = new_dot;

    return s_success;
}

Bool_t is_zero(const Number *const number) {
    //design time check.
    assert(number);

    //get a traverser.
    Digit_Node *trav = number->head;

    //traverse
    while(trav) {
	//skip dot.
	if(trav->digit == '.') {
	    //goto next digit.
	    trav = trav->next;
	    continue;
	}

	//check digit.
	if(trav->digit)
	    return b_false;

	//goto next digit.
	trav = trav->next;
    }

    return b_true;
}

/* Function to convert fractional numbers to whole
   ending with a '.0'

   returns the factor (power of ten) by which the
   number was multiplied to make it whole.
 */
int make_whole(Number *const number) {
    //design time check.
    assert(number);

    //the multiplying factor (power of ten).
    int factor = number->tail->distance_from_dot;

    //no decimal dot in number.
    if(factor < 0) {
	//append '.0'
	insert_at_last('.', number);
	insert_at_last('0', number);
	assign_place_value(number);

	//multiplied by 10^0.
	return 0;
    }

    //we're here: there's a decimal dot. Go below.

    //multiply by powers of ten.
    modify_order_of_magnitude(number, factor);
    assign_place_value(number);

    return factor;
}
