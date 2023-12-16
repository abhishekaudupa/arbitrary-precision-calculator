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

    //return variable.
    Number number = { NULL, NULL, '+' };

    //check for explicit sign of the number.
    if(is_sign(number_string[0])) {
	number.sign = number_string[0];
	++i;
    }

    //discard preceding zeroes, if any.
    while(number_string[i] == '0')
	++i;

    //if the input was a zero
    if(!number_string[i])
	--i;

    //check if the number string starts with a dot.
    if(number_string[i] == '.') {
	//number now starts with a zero.
	insert_at_last('0', &(number.head), &(number.tail));
    }

    //traverse the number string.
    while(number_string[i]) {
	//insert the digit at the last node.
	insert_at_last(number_string[i], &(number.head), &(number.tail));
	++i;
    }

    //assign place values to digits.
    assign_place_value(&number);

    return number;
}

Status insert_at_last(const char digit, Digit_Node **head, Digit_Node **tail) {

    //design time verification.
    assert(head && tail);

    //get memory for a new digit.
    Digit_Node *new = get_memory(sizeof(*new));

    //if allocation fails.
    if(!new)
	return s_failure;

    //set the digit
    new->digit = (digit == '.')? digit: digit - '0';

    //check if the list is empty
    if(!*head) {

	//set head and tail.
	*head = *tail = new;

	//set links
	new->prev = NULL;
	new->next = NULL;

	return s_success;
    }

    //if list isn't empty, go below.

    //set new after tail.
    (*tail)->next = new;

    //set new's links.
    new->next = NULL;
    new->prev = *tail;

    //increment tail.
    *tail = new;

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

Status insert_at_first(const char digit, Digit_Node **head) {

    //design time verification.
    assert(head);

    //list shouldn't be empty.
    assert(*head);

    //data should not be decimal dot.
    assert(digit != '.');

    //get memory for a new digit.
    Digit_Node *new = get_memory(sizeof(*new));

    //if allocation fails.
    if(!new)
	return s_failure;

    //set the digit
    new->digit = digit - '0';

    //set new's links.
    new->next = *head;
    new->prev = NULL;

    //set new before head.
    (*head)->prev = new;

    //decrement head.
    *head = new;

    return s_success;
}