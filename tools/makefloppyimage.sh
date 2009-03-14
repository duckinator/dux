#!/bin/sh

losetup /dev/loop0 $2
mount /dev/loop0 $1
cp $3 $1/$3
cp $3.map $1/$3.map
umount /dev/loop0
losetup -d /dev/loop0

