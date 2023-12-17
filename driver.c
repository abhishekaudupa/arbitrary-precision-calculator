#include <stdio.h>
#include "argument.h"
#include "number.h"
#include "allocator.h"
#include "add.h"
#include "subtract.h"
#include "operation.h"
#include "multiply.h"

int main(int argc, char **argv) {

    //validate input arithmetic CL arguments.
    if(validate_arguments(argc, argv) == s_failure) {
	fprintf(stderr, "Arguments invalid!\n");
	return 1;
    }

    //get numbers from arguments.
    Number num1 = get_number(argv[1]);
    //Number num2 = get_number(argv[3]);
    //char operator = argv[2][0];

    int n;
    scanf("%d", &n);
    modify_order_of_magnitude(&num1, n);

    print_number(&num1);
    printf("\n");

    release_memory();
}
