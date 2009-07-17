SOURCES = $(shell find . -mindepth 1 -maxdepth 3 -name "*.c") $(shell find . -mindepth 1 -maxdepth 3 -name "*.s")
TOBJECTS = $(SOURCES:.c=.o)
#OBJECTS = $(TOBJECTS:.asm=.o)
OBJECTS = $(TOBJECTS:.s=.o)

CC = gcc
LD = ld
AS = nasm

CFLAGS = -Iinclude -I../include
LDFLAGS = 
ASFLAGS =

all: lib.lib

lib.lib: $(OBJECTS)
	$(LD) $(LDFLAGS) -melf_i386 -r -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -m32 -c -o $@ $<

%.o: %.s
#asm
	$(AS) $(ASFLAGS) -felf32 -o $@ $<

clean:
	-rm *.o lib.lib

.PHONY: all lib.lib clean
