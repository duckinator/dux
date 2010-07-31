#!/bin/sh

# Create blank image to contain file data
dd bs=1024 count=1439 if=/dev/zero of=tmp

# Format file image
mkfs.msdos tmp

# Create ./floppy directory
mkdir floppy

# Enable/configure loopback 1
losetup /dev/loop1 tmp

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

# Create blank floppy image
dd bs=1024 count=1440 if=/dev/zero of=Dux.img

# Copy file data to floppy image
dd ibs=1024 obs=512 seek=1 count=1439 if=tmp of=Dux.img conv=notrunc

# Copy bootloader to floppy image
dd bs=512 count=1 if=beef/isofs/boot of=Dux.img conv=notrunc

# Delete ./tmp
rm tmp
