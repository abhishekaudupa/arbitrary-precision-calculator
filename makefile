apcalc : argument.o driver.o allocator.o number.o add.o subtract.o operation.o multiply.o divide.o
	gcc -Wall argument.o driver.o allocator.o number.o add.o subtract.o operation.o multiply.o divide.o -o apcalc

argument.o : argument.c argument.h common.h
	gcc -Wall -c argument.c -o argument.o

driver.o : driver.c argument.o number.o allocator.o operation.o
	gcc -Wall -c driver.c -o driver.o

allocator.o : allocator.c allocator.h common.h
	gcc -Wall -c allocator.c -o allocator.o

number.o : number.c number.h common.h
	gcc -Wall -c number.c -o number.o

add.o : add.c add.h number.o
	gcc -Wall -c add.c -o add.o

subtract.o : subtract.c subtract.h number.o
	gcc -Wall -c subtract.c -o subtract.o

operation.o : operation.c operation.h number.o add.o subtract.o
	gcc -Wall -c operation.c -o operation.o

multiply.o : multiply.c multiply.h number.o allocator.o
	gcc -Wall -c multiply.c -o multiply.o

divide.o : divide.c divide.h number.o subtract.o allocator.o
	gcc -Wall -c divide.c -o divide.o

clean :
	rm *.o apcalc
	clear
