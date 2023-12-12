 #include <stdio.h>
#include "argument.h"
#include "number.h"
#include "allocator.h"
#include "operation.h"

#ifndef NDEBUG
void run_tests() {
    test_arguments_c();
}
#endif

int main(int argc, char **argv) {
#ifndef NDEBUG
    run_tests();
#endif

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

    Number *sum = add(&num1, &num2);
    printf("Sum: ");
    print_number(sum);
    printf("\n");

    release_memory();
}
