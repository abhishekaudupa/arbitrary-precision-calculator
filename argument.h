#ifndef ARGUMENT_H
#define ARGUMENT_H

#include "common.h"

Status validate_arguments(const int argc, char **const argv);

Status is_digit(const char c);

Status is_sign(const char c);

Status is_decimal_point(const char c);

Status validate_operand(const char *const operand_string);

Status validate_operator(const char *const operator_string);

void test_arguments_c();

void test_validate_arguments();

void test_validate_operand();

#endif
