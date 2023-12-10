#include <stdio.h>
#include "argument.h"
#include "common.h"

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
}

