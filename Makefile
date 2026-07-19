#   make        build the test program
#   make test   build and run it
#   make clean  remove build artifacts

CC      := gcc
AS      := nasm

CFLAGS  := -std=c17 -O2 -Wall -Wextra -Wpedantic -Iinclude
ASFLAGS := -f elf64

BIN     := test_mandelbrot
OBJ     := src/test_mandelbrot.o asm/mandelbrot_pixel.o

.PHONY: all test clean

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

asm/%.o: asm/%.asm
	$(AS) $(ASFLAGS) -o $@ $<

test: $(BIN)
	./$(BIN)

clean:
	rm -f $(OBJ) $(BIN)
