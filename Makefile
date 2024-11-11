# Name of the output executable
TARGET = bigletters

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -O2

# Source files
SRCS = bigletters.c

# Object files (automatically converts .c filenames to .o)
OBJS = $(SRCS:.c=.o)

# Default target to build the executable
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets (not actual files)
.PHONY: all clean run
