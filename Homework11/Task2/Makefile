CC = gcc
CFLAGS = -Wall -Wextra -pedantic

all: pipe_app child_process

pipe_app: pipe_app.o
	$(CC) $(CFLAGS) -o pipe_app pipe_app.o

pipe_app.o: pipe_app.c
	$(CC) $(CFLAGS) -c pipe_app.c

child_process: child_process.o
	$(CC) $(CFLAGS) -o child_process child_process.o

child_process.o: child_process.c
	$(CC) $(CFLAGS) -c child_process.c

clean:
	rm -f *.o pipe_app child_process