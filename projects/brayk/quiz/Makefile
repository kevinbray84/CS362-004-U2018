CFLAGS = -Wall -fpic -coverage -lm -std=c99

default: test

test: testme.c
	gcc -o testme -g testme.c $(CFLAGS)
	./testme
	gcov testme.c -b

clean:
	rm -f testme testme.gcno testme.c.gcov testme.gcda