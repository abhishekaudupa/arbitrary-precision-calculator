#include <stdio.h>
#include "argument.h"
#include "number.h"
#include "allocator.h"

#ifndef NDEBUG
void run_tests() {
    test_arguments_c();
}
#endif

int main(int argc, char **argv) {
#ifndef NDEBUG
    run_tests();
#endif

    if(validate_arguments(argc, argv) == s_failure) {
	fprintf(stderr, "Arguments invalid!\n");
	return 1;
    }

    Number num1 = get_number(argv[1]);
    print_number(&num1);
    printf("\n");

    Number num2 = get_number(argv[3]);
    print_number(&num2);
    printf("\n");

    release_memory();
}
