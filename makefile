apcalc : argument.o driver.o allocator.o
	gcc -Wall argument.o driver.o allocator.o -o apcalc

argument.o : argument.c argument.h common.h
	gcc -Wall -c argument.c -o argument.o

driver.o : driver.c common.h
	gcc -Wall -c driver.c -o driver.o

allocator.o : allocator.c allocator.h common.h
	gcc -Wall -c allocator.c -o allocator.o

clean :
	rm *.o
