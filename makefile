apcalc : argument.o driver.o allocator.o number.o
	gcc -Wall argument.o driver.o allocator.o number.o -o apcalc

argument.o : argument.c argument.h common.h
	gcc -Wall -c argument.c -o argument.o

driver.o : driver.c common.h
	gcc -Wall -c driver.c -o driver.o

allocator.o : allocator.c allocator.h common.h
	gcc -Wall -c allocator.c -o allocator.o

number.o : number.c number.h common.h
	gcc -Wall -c number.c -o number.o

clean :
	rm *.o apcalc
	clear
