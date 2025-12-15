TARGET_TEST = my_axpy_test
TARGET_MEASURE = my_axpy_measure
C_SOURCES = main.c axpy.c
CC = gcc

# Standard Compiler Flags: -O3 is required for runtime measurement
# -Wall enables common warnings
CFLAGS = -Wall -O3

LDFLAGS = -lm #math library


# 1. Default Target: Compile for Testing
all: $(TARGET_TEST)

$(TARGET_TEST): $(C_SOURCES)
	$(CC) $(CFLAGS) $(C_SOURCES) -o $(TARGET_TEST) $(LDFLAGS)


# 2. Measurements Target:
measurements: $(C_SOURCES)
	$(CC) $(CFLAGS) -DMEASUREMENTS $(C_SOURCES) -o $(TARGET_MEASURE) $(LDFLAGS)
	# Execute the program
	./$(TARGET_MEASURE)

# 3. Clean Target
clean:
	rm -f $(TARGET_TEST) $(TARGET_MEASURE) measurements.csv

.PHONY: all clean measurements

