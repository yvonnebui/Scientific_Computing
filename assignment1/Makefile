CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OUTPUT = horner

# Target 1: compile the program
all: horner.c
        $(CC) $(CFLAGS) -o $(OUTPUT) horner.c -lm

# Target 2: delete binary files
clean:
        rm -f $(OUTPUT) *.o

.PHONY: all clean


