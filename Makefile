# Makefile
# Compile Dux.
#
# 2008 Copyright © Martin Brandenburg

AS=yasm
CC=gcc
LD=ld

ASFLAGS=-felf -gstabs
LDFLAGS=-melf_i386 -Tlink.ld -Map dux.map -g
CFLAGS=-m32 -fno-builtin -fno-stack-protector -Iinclude -Idrivers -Imm -g -DDEBUG

-include config.mk

OBJS=boot/loader.o boot/exceptions.o boot/descriptor_tables.o boot/irqs.o boot/irq_handler.o boot/gdt.o boot/isrs.o boot/idt.o boot/loadidt.o 
OBJS+=kernel/panic.o kernel/timer.o kernel/printk.o kernel/task.o kernel/syscall.o kernel/misc.o
OBJS+=init/init.o kernel/stack_dump.o

# Memory
OBJS += mm/memory.o

# Drivers
OBJS += drivers/core/ports.o drivers/core/screen.o drivers/core/console.o \
drivers/core/kb.o

all: dux

incbn: all
	@python tools/incbn.py

.s.o:
	@echo "  AS      $@"
	@$(AS) $(ASFLAGS) -o $@ $<

.c.o:
	@echo "  CC      $@"
	@$(CC) $(CFLAGS) -o $@ -c $<

dux: $(OBJS)
	@echo "  LD      $@"
	@$(LD) $(LDFLAGS) -o dux $(OBJS)

image: dux
	@echo "  IMAGE   image"
	@mkdir /tmp/dux
	@cp tools/disk/boot-floppy.img /tmp/dux.img
	@sudo sh tools/makefloppyimage.sh /tmp/dux /tmp/dux.img dux
	@mv /tmp/dux.img ./image
	@rmdir /tmp/dux

clean:
	@echo "  CLEAN   image dux dux.map $(OBJS)"
	@-rm image dux dux.map $(OBJS)

.PHONY: all clean incbn

