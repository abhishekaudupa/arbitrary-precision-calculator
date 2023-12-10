apcalc : argument.o driver.o
	gcc -Wall argument.o driver.o -o apcalc

argument.o : argument.c argument.h common.h
	gcc -Wall -c argument.c -o argument.o

driver.o : driver.c common.h
	gcc -Wall -c driver.c -o driver.o
