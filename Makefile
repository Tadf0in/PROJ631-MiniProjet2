# Variables
CC = gcc
CFLAGS = -Wall -Wextra -I.\src -std=gnu99
SRC = src/alphabet.c
OBJ = $(SRC:.c=.exe)

# Targets
all: compile_tests

# Executable targets
...: executables\....c $(OBJ)
		$(CC) $(CFLAGS) $^ -o $@.exe

# Test compilation target
TESTS = $(patsubst tests/%.c,tests/%.exe,$(wildcard tests/*.c))

compile_tests: $(TESTS)

tests/%.exe: tests\%.c $(OBJ)
		$(CC) $(CFLAGS) $< $(OBJ) -o $@

# Test execution target
run_tests: compile_tests
		@for test in $(TESTS); do \
				echo "Running $$test..."; \
				$$test || exit 1; \
		done

# Compilation of object files
$(OBJ): %.exe: %.c
		$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
		del /Q *.exe ... $(TESTS)

.PHONY: all clean compile_tests run_tests