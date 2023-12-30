#ifndef NUMBER_H
#define NUMBER_H

#include "common.h"

//number represented as a linked list (without sign).
typedef struct _Digit_Node {
    unsigned char digit;
    int distance_from_dot;
    struct _Digit_Node *next;
    struct _Digit_Node *prev;
} Digit_Node;

//number represented with a linked list (with sign).
typedef struct _Number {
    Digit_Node *head;
    Digit_Node *tail;
    char sign;
} Number;

Number get_number(const char *const number_string);

Status insert_at_last(const char digit, Number *const number);

void print_number(const Number *const number);

void assign_place_value(const Number *const number);

Bool_t abs_greater_than(const Number *const num1, const Number *const num2);

Status insert_at_first(const char digit, Number *const number);

unsigned int get_digit_count(const Number *const number);

Status modify_order_of_magnitude(Number *const number, int magnitude_delta);

Status insert_after(const char digit_to_insert, Digit_Node *const digit);

Bool_t is_zero(const Number *const number);

int make_whole(Number *const number);

void sanitize(Number *const number);

#endif
