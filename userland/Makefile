SOURCES = $(shell find . -mindepth 1 -maxdepth 3 -name "*.c") $(shell find . -mindepth 1 -maxdepth 3 -name "*.s")
TOBJECTS = $(SOURCES:.c=.o)
#OBJECTS = $(TOBJECTS:.asm=.o)
OBJECTS = $(TOBJECTS:.s=.o)

CC = gcc
LD = ld
AS = nasm

CFLAGS = -Iinclude -I../include-MAKE
LDFLAGS = 
ASFLAGS =

all: userland.lib

userland.lib: $(OBJECTS)
	$(LD) $(LDFLAGS) -melf_i386 -r -o $@ $(OBJECTS)
	#@echo -n

%.o: %.c
	$(CC) $(CFLAGS) -m32 -c -o $@ $<

%.o: %.s
#asm
	$(AS) $(ASFLAGS) -felf32 -o $@ $<

clean:
	-rm *.o userland.lib

.PHONY: all userland.lib clean
