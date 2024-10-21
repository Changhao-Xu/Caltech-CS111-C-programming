#
# CS 11 C track: Makefile for assignment 5.
#

CC = gcc
CFLAGS = -g -Wall -Wstrict-prototypes -ansi -pedantic -Wuninitialized

all: lab5_array lab5_pointer

lab5_array: lab5_array.o memcheck.o
	$(CC) lab5_array.o memcheck.o -o lab5_array

lab5_pointer: lab5_pointer.o memcheck.o
	$(CC) lab5_pointer.o memcheck.o -o lab5_pointer

memcheck.o: memcheck.c memcheck.h
	$(CC) $(CFLAGS) -c memcheck.c

lab5_array.o: lab5_array.c memcheck.h
	$(CC) $(CFLAGS) -c lab5_array.c

lab5_pointer.o: lab5_pointer.c memcheck.h
	$(CC) $(CFLAGS) -c lab5_pointer.c

check:
	c_style_check lab5_array.c lab5_pointer.c

clean:
	rm -f *.o lab5_array lab5_pointer

