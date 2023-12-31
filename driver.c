#include <stdio.h>
#include "argument.h"
#include "number.h"
#include "allocator.h"
#include "operation.h"

int main(int argc, char **argv) {

    //validate input arithmetic CL arguments.
    if(validate_arguments(argc, argv) == s_failure) {
	fprintf(stderr, "Arguments invalid!\n");
	return 1;
    }

    //get numbers and operator from arguments.
    Number num1 = get_number(argv[1]);
    Number num2 = get_number(argv[3]);
    char operator = argv[2][0];

    //print the result of the operation.
    print_number(resolve(&num1, &num2, operator));
    printf("\n");

    //free memory.
    release_memory();
}
