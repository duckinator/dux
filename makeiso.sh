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

./copymodules.sh

if [ `uname -s` = "Darwin" ]; then
	hdiutil makehybrid -iso -o dux.iso \
		-eltorito-boot isofs/boot/grub/stage2_eltorito \
		-no-emul-boot isofs
else
	$isocmd -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -input-charset utf-8 -o dux.iso isofs
fi

# Instead of calling -boot-info-table, we use tools/bootinfo, so it doesn't modify stage2_eltorito.
# Why doesn't -boot-info-table just modify the iso, you ask? I'd like to know as well...
./tools/bootinfo isofs/boot/grub/stage2_eltorito dux.iso

mv dux.iso iso
