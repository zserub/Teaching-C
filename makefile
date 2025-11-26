# create variables
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Wformat=2 -Werror -std=c23
TARGET = calculator

# command to build everything
all: $(TARGET)

# attach source to output
$(TARGET): calculator.c
	$(CC) $(CFLAGS) $< -o $@
# concat strings, $<: source file, $@ output/target file