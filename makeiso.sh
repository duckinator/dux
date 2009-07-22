#!/bin/sh

# FIX YOUR OWN OS!
# THIS IS NOT OUR RESPONSIBILITY
# THIS WILL BE REMOVED 21 AUG 2009
isocmd="genisoimage"

if [ ! -e 'isofs/boot/grub/stage2_eltorito' ]
then
	echo 'You need to locate stage2_eltorito and put it in ./isofs/boot/grub'
	exit
fi

if [ ! -e '/usr/bin/genisoimage' ]
then
	echo "FIX YOUR OWN OS!"
	echo "THIS IS NOT OUR RESPONSIBILITY"
	echo "THIS WILL BE REMOVED 21 AUG 2009"
	isocmd="mkisofs"
fi

mkdir -p isofs/boot/grub
mkdir -p isofs/System
cp krnl/krnl isofs/System/
touch isofs/boot/grub/menu.lst
echo "default 0" >> isofs/boot/grub/menu.lst
echo "timeout 1" >> isofs/boot/grub/menu.lst
echo "title Dux" >> isofs/boot/grub/menu.lst
echo "kernel /System/krnl" >> isofs/boot/grub/menu.lst
$isocmd -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -input-charset utf-8 -o Dux.iso isofs
