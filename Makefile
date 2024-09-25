CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: mmix instructions

mmix: mmix.c mmix.h
	$(CC) $(CFLAGS) -DMMIX_STANDALONE mmix.c -o mmix

mmix.o: mmix.c mmix.h
	$(CC) $(CFLAGS) -c mmix.c -o mmix.o

instructions: instructions.c mmix.o mmix.h
	$(CC) $(CFLAGS) instructions.c mmix.o -o instructions

clean:
	rm -f mmix instructions mmix.o
