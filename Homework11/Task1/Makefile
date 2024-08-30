# UNIX & Windows compatible Makefile
CC = gcc
CFLAGS = -Wall -Wextra -pedantic
LIB = libfilecopy.a
all: main

libfilecopy.a: file_copy.o
	ar rcs $(LIB) file_copy.o

file_copy.o: file_copy.c file_copy.h
	$(CC) $(CFLAGS) -c file_copy.c

main: main.o libfilecopy.a
	$(CC) $(CFLAGS) -o main main.o -L. -lfilecopy

main.o: main.c file_copy.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o main libfilecopy.a