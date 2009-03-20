#!/bin/sh

losetup /dev/loop1 $2
mount /dev/loop1 $1
cp $3 $1/$3
cp $3.map $1/$3.map
umount /dev/loop1
losetup -d /dev/loop1

