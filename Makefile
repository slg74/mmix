CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -DMMIX_STANDALONE

all: mmix

mmix: mmix.c instructions.c mmix.h instructions.h
	$(CC) $(CFLAGS) mmix.c instructions.c -o mmix

clean:
	rm -f mmix