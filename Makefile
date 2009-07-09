# Makefile
# Compile Dux.
#
# 2008 Copyright © Martin Brandenburg

AS=nasm
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
OBJS += kernel/mm.o

# Drivers
OBJS += drivers/core/ports.o drivers/core/screen.o drivers/core/console.o \
drivers/core/kb.o

all: iso

incbn: all
	@python tools/incbn.py

.s.o:
	@echo "  AS      $@"
	@$(AS) $(ASFLAGS) -o $@ $<

.c.o:
	@echo "  CC      $@"
	@$(CC) $(CFLAGS) -o $@ -c $<

hal/hal.lib:
	(cd hal; make)

dux: hal/hal.lib $(OBJS)
	@echo "  LD      $@"
	@$(LD) $(LDFLAGS) -o dux hal/hal.lib $(OBJS)

image: dux
	@echo "  IMAGE   image"
	@mkdir /tmp/dux
	@cp tools/disk/boot-floppy.img /tmp/dux.img
	@sudo sh tools/makefloppyimage.sh /tmp/dux /tmp/dux.img dux
	@mv /tmp/dux.img ./image
	@rmdir /tmp/dux

iso: dux
	mkdir -p isofiles/boot/grub
	cp /boot/grub/stage2_eltorito ./isofiles/boot/grub
	cp ./dux ./isofiles/boot/dux
	touch ./isofiles/boot/grub/menu.lst
	echo "default 0" >> ./isofiles/boot/grub/menu.lst
	echo "timeout 1" >> ./isofiles/boot/grub/menu.lst
	echo "title Dux" >> ./isofiles/boot/grub/menu.lst
	echo "kernel /boot/dux" >> ./isofiles/boot/grub/menu.lst
	echo "module /boot/dux" >> ./isofiles/boot/grub/menu.lst
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o Dux.iso isofiles
	rm -r ./isofiles

clean:
	@echo "  CLEAN   image Dux.iso dux dux.map $(OBJS)"
	@-rm image Dux.iso dux dux.map $(OBJS)
	(cd hal; make clean)

.PHONY: all clean incbn iso

