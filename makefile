CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -std=c99 -pedantic -O3

builddate: builddate.o
	$(CC) builddate.o -o builddate

builddate.o: builddate.c
	$(CC) $(CFLAGS) builddate.c

clean:
	rm *.o builddate
