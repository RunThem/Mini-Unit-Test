all: mut.h example.c
	$(CC) -Wall -o example example.c && ./example
