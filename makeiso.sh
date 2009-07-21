#!/bin/sh

mkdir -p isofs/boot/grub
mkdir -p isofs/System
cp /boot/grub/stage2_eltorito isofs/boot/grub/
cp krnl/krnl isofs/System/
touch isofs/boot/grub/menu.lst
echo "default 0" >> isofs/boot/grub/menu.lst
echo "timeout 1" >> isofs/boot/grub/menu.lst
echo "title Dux" >> isofs/boot/grub/menu.lst
echo "kernel /System/krnl" >> isofs/boot/grub/menu.lst
genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -input-charset utf-8 -o Dux.iso isofs
rm -r ./isofs
