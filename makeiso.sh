#!/bin/sh

isocmd="genisoimage"

rm -rf isofs/System/

mkdir -p isofs/boot/grub

if [ ! -e '/usr/bin/genisoimage' ]
then
	isocmd="mkisofs"
fi

mkdir -p isofs/System isofs/Modules

cp src/metodo/metodo.exe isofs/System
cp src/user/userland.exe isofs/System

for x in `find src -name '*.lib'`; do
  cp $x isofs/System
done

for x in `find src/modules -name '*.exe'`; do
  echo "Copying $x"
  cp $x isofs/Modules
done

$isocmd -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -input-charset utf-8 -o dux.iso isofs

mv dux.iso iso
