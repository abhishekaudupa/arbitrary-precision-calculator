 #include <stdio.h>
#include "argument.h"
#include "number.h"
#include "allocator.h"
#include "add.h"
#include "subtract.h"

int main(int argc, char **argv) {

    //validate input arithmetic CL arguments.
    if(validate_arguments(argc, argv) == s_failure) {
	fprintf(stderr, "Arguments invalid!\n");
	return 1;
    }

    //get numbers from arguments.
    Number num1 = get_number(argv[1]);
    Number num2 = get_number(argv[3]);

    printf("Num1: ");
    print_number(&num1);
    printf("\n");
    printf("Num2: ");
    print_number(&num2);
    printf("\n");

    Number *sum = subtract(&num1, &num2);
    printf("Difference: ");
    print_number(sum);
    printf("\n");

    release_memory();
}
