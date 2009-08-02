#!/bin/sh

# FIX YOUR OWN OS!
# THIS IS NOT OUR RESPONSIBILITY
# THIS WILL BE REMOVED 21 AUG 2009
isocmd="genisoimage"

rm -rf isofs/System/

mkdir -p isofs/boot/grub

if [ ! -e 'isofs/boot/grub/stage2_eltorito' ]
then
	if [ -e /boot/grub/stage2_eltorito ]
	then
		echo "Can't find stage2_eltorito in ./isofs/boot/grub, copying from /boot/grub/"
		cp /boot/grub/stage2_eltorito isofs/boot/grub/stage2_eltorito
	else
		echo 'You need to locate stage2_eltorito and put it in ./isofs/boot/grub'
		exit
	fi
fi

if [ ! -e '/usr/bin/genisoimage' ]
then
	echo "FIX YOUR OWN OS!"
	echo "THIS IS NOT OUR RESPONSIBILITY"
	echo "THIS WILL BE REMOVED 21 AUG 2009"
	isocmd="mkisofs"
fi

mkdir -p isofs/System

cp src/metodo/metodo.exe isofs/System/
cp src/krnl/krnl.exe isofs/System/
cp src/user/user.exe isofs/System/userland
cp src/lib/krnllib/krnllib.lib isofs/System/

rm isofs/boot/grub/menu.lst
touch isofs/boot/grub/menu.lst
echo "default 0" > isofs/boot/grub/menu.lst
echo "timeout 1" >> isofs/boot/grub/menu.lst
echo "title Metodo Dux" >> isofs/boot/grub/menu.lst
echo "kernel /System/metodo.exe" >> isofs/boot/grub/menu.lst
echo "title Standard Dux" >> isofs/boot/grub/menu.lst
echo "kernel /System/krnl.exe" >> isofs/boot/grub/menu.lst
echo "module /System/userland" >> isofs/boot/grub/menu.lst
$isocmd -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -input-charset utf-8 -o Dux.iso isofs
