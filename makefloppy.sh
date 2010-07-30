#!/bin/sh

dd bs=1024 count=1440 if=/dev/zero of=Dux.img
mkfs.msdos fdd.img

mkdir mnt
losetup /dev/loop1 fdd.img
mount /dev/loop1 mnt
cp -r isofs/* mnt
#cp $3.map $1/$3.map
umount /dev/loop1
losetup -d /dev/loop1
rmdir mnt
dd bs=512 count=1 if=isofs/boot/boot of=Dux.img conv=notrunc
