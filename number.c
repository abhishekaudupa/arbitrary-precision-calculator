#include "number.h"
#include "argument.h"
#include "allocator.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

Number get_number(const char *number_string) {

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
