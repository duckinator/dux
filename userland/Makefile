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

all: userland

userland: $(OBJECTS)
	@echo -n

%.o: %.c
	$(CC) $(CFLAGS) -m32 -c -o $@ $<

%.o: %.s
#asm
	$(AS) $(ASFLAGS) -felf32 -o $@ $<

clean:
	-rm *.o *.app

.PHONY: all clean
