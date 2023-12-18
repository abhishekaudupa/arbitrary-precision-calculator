#include "argument.h"
#include <assert.h>
#include <string.h>

Status validate_arguments(const int argc, char **const argv) {

    //design time validation.
    assert(argc > 0 && argv);

    //we should have 4 arguments: 1 filename, 2 operands and 1 operator.
    if(argc != 4) {
	return s_failure;
    }

    //get validation status for operands and operators.
    Status validation_status_operand1 = validate_operand(argv[1]);
    Status validation_status_operand2 = validate_operand(argv[3]);
    Status validation_status_operator = validate_operator(argv[2]);

    //return the final validation status of all arguments.
    return validation_status_operand1
	&& validation_status_operand2
	&& validation_status_operator;
}

inline Status is_digit(const char c) {
    return (c >= '0' && c <= '9');
}

inline Status is_sign(const char c) {
    return (c == '+' || c == '-');
}

inline Status is_decimal_point(const char c) {
    return c == '.';
}

Status validate_operand(const char *const operand_string) {

    //design time validation.
    assert(operand_string);

    //get the string length.
    size_t operand_string_length = strlen(operand_string);

    //check if it's a single digit.
    if(operand_string_length == 1) {
	if(!is_digit(operand_string[0]))
	    return s_failure;
    }

    //decimal point presence flag.
    char decimal_point = 0;

    //check whether the first character is a digit, sign or a decimal point.
    if(!is_digit(operand_string[0])) {
	if(!is_sign(operand_string[0])) {
	    if(!is_decimal_point(operand_string[0])) {
		return s_failure;
	    }
	    else
		decimal_point = 1;
	}
    }

    //check if rest of the characters form a valid number.
    for(size_t i = 1; i < operand_string_length; ++i) {
	if(!is_digit(operand_string[i])) {
	    if(is_decimal_point(operand_string[i])) {
		if(decimal_point) {
		    return s_failure;
		}
		else
		    decimal_point = 1;
	    } else {
		return s_failure;
	    }
	}
    }

    //ensure the number doesn't end with a decimal point.
    if(is_decimal_point(operand_string[operand_string_length - 1])) {
	return s_failure;
    }

    return s_success;
}

Status validate_operator(const char *const operator_string) {

    //design time validation.
    assert(operator_string);

    //check if string is longer than 1 character.
    if(strlen(operator_string) > 1)
	return s_failure;

    //check if string is a valid arithmetic operator.
    return operator_string[0] == '+'
	|| operator_string[0] == '-'
	|| operator_string[0] == 'x'
	|| operator_string[0] == 'X'
	|| operator_string[0] == '/';
}
