#include <stdio.h>
#include "argument.h"
#include "number.h"
#include "allocator.h"
#include "add.h"
#include "subtract.h"
#include "operation.h"

int main(int argc, char **argv) {

    //validate input arithmetic CL arguments.
    if(validate_arguments(argc, argv) == s_failure) {
	fprintf(stderr, "Arguments invalid!\n");
	return 1;
    }

    //get numbers from arguments.
    Number num1 = get_number(argv[1]);
    Number num2 = get_number(argv[3]);
    char operator = argv[2][0];

    print_number(&num1);
    printf(" %c ", operator);
    print_number(&num2);
    printf(" = ");
    Number *result = resolve(&num1, &num2, operator);
    print_number(result);
    printf("\n");

    release_memory();
}
