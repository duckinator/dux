#!/bin/sh

dd bs=1024 count=1440 if=/dev/zero of=Dux.img

mkfs.msdos Dux.img


# Create ./floppy
mkdir floppy

# Enable/configure loopback 1
losetup /dev/loop1 Dux.img

# Mount loopback 1
mount /dev/loop1 floppy

# Copy everything from isofs/ to floppy/
cp -r isofs/* floppy/

# Unmount loopback 1
umount /dev/loop1

# Disable loopback 1
losetup -d /dev/loop1

# Delete ./floppy
rmdir floppy

# Copy bootloader
dd bs=512 count=1 if=isofs/boot/boot of=Dux.img conv=notrunc
