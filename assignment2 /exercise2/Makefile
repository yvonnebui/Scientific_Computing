CC = gcc
# -std=c99 for complex number support; -lm is for math library
CFLAGS = -std=c99 -Wall -Wextra -I.
LDFLAGS = -lm

TARGET = numerical_diff
SRC = numerical_diff.c
DOCFILE = Doxyfile

# Default target: Compile and link
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDFLAGS)

# Target to run the program
run: $(TARGET)
	./$(TARGET)

# Target to generate Doxygen documentation
doc: $(DOCFILE)
	doxygen $(DOCFILE)

# Target to clean up generated files
clean:
	rm -f $(TARGET) *.o numerical_diff.txt
	rm -rf doc html latex

.PHONY: all run doc clean

