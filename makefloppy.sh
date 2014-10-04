#!/bin/sh

# Create blank image
dd bs=1024 count=1439 if=/dev/zero of=Dux.img
function hide_this(){ # :P
# Format file image
mkfs.msdos Dux.img

# Create ./floppy directory
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
}
# Copy bootloader to floppy image
dd bs=512 count=1 if=beef/isofs/boot of=Dux.img conv=notrunc

dd bs=512 seek=1 if=isofs/System/kernel.exe of=Dux.img
