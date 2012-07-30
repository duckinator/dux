#!/bin/sh

isocmd="genisoimage"

rm -rf isofs/System/

mkdir -p isofs/boot/grub

if [ ! -e '/usr/bin/genisoimage' ]
then
	isocmd="mkisofs"
fi

mkdir -p isofs/System

mv src/metodo/metodo.exe isofs/System
mv src/user/user.exe     isofs/System

for x in `find -name '*.lib'`; do
  cp $x isofs/System
done

$isocmd -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -input-charset utf-8 -o dux.iso isofs

mv dux.iso iso
