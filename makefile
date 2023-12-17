apcalc : argument.o driver.o allocator.o number.o add.o subtract.o operation.o
	gcc -Wall argument.o driver.o allocator.o number.o add.o subtract.o operation.o -o apcalc

argument.o : argument.c argument.h common.h
	gcc -Wall -c argument.c -o argument.o

driver.o : driver.c argument.h number.h allocator.h add.h
	gcc -Wall -c driver.c -o driver.o

allocator.o : allocator.c allocator.h common.h
	gcc -Wall -c allocator.c -o allocator.o

number.o : number.c number.h common.h
	gcc -Wall -c number.c -o number.o

add.o : add.c add.h
	gcc -Wall -c add.c -o add.o

subtract.o : subtract.c subtract.h
	gcc -Wall -c subtract.c -o subtract.o

operation.o : operation.c operation.h number.h add.h subtract.h
	gcc -Wall -c operation.c -o operation.o

clean :
	rm *.o apcalc
	clear
	ls
