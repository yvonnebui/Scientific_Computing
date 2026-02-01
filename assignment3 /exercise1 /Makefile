# Executable name
TARGET = solver_test

# Source files
C_SOURCES = main.c dense_solvers.c matrix.c

# Compiler
CC = gcc

# Required compiler flags (Task 1a)
CFLAGS = -std=c11 -O2 -Wall -Wextra

# Libraries to link
LDFLAGS = -llapacke -lopenblas -lm

all: $(TARGET)

$(TARGET): $(C_SOURCES)
	$(CC) $(CFLAGS) $(C_SOURCES) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET) dense_mat.txt

clean:
	rm -f $(TARGET)

.PHONY: all clean run
