CC      ?= gcc
CFLAGS  ?= -std=c11 -O2 -Wall -Wextra -Wpedantic -g
CPPFLAGS = -Iinclude -MMD -MP

SRC  = $(wildcard src/*.c)
OBJ  = $(SRC:src/%.c=build/%.o)
BIN  = bin/compare

all: $(BIN)

$(BIN): $(OBJ) build/compare.o | bin
	$(CC) $(CFLAGS) $^ -o $@

build/%.o: src/%.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

build/compare.o: tests/compare.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

build bin:
	mkdir -p $@

test: $(BIN)
	./$(BIN) data/fil_rouge.ctx

clean:
	rm -rf build bin

-include build/*.d

.PHONY: all test clean
