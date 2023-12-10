#ifndef NUMBER_H
#define NUMBER_H

#include "common.h"

//number represented as a linked list (without sign).
typedef struct _Number_Unsigned {
    unsigned char digit;
    struct _Number_Unsigned *next;
    struct _Number_Unsigned *prev;
} Number_Unsigned;

//number represented with a linked list (with sign).
typedef struct _Number {
    Number_Unsigned *head;
    Number_Unsigned *tail;
    char sign;
} Number;

Number get_number(const char *number_string);

Status insert_at_last(const char digit, Number_Unsigned **head, Number_Unsigned **tail);

void print_number(const Number *number);

#endif
