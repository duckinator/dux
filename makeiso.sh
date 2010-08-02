#!/bin/sh

isocmd="genisoimage"

bootloader="$1"

which genisoimage
if [ $? -ne 0 ]; then
	isocmd="mkisofs"
fi

if [ -e "iso/Dux.iso" ]; then
	rm iso/Dux.iso
fi

if [ -e "isofs/System" ]; then
	rm -r isofs/System
fi

if [ -e "isofs/boot" ]; then
	rm -r isofs/boot
fi

if [ -e "isofs/Drivers" ]; then
	rm -r isofs/Drivers
fi

mkdir -p isofs/System
mkdir -p isofs/Drivers
mkdir -p isofs/boot

cp src/metodo/metodo.exe isofs/System/
cp src/user/user.exe isofs/System/userland.exe
cp src/lib/krnllib/krnllib.lib isofs/System/

echo > drivers.tmp
for f in $(ls src/metodo/driver/*/*.exe); do
	filename=$(echo $f | sed "s/src\/metodo\/driver\/.*\///")
	cp "$f" "isofs/Drivers/$filename"
	echo "$filename" >> drivers.tmp
done

mkdir -p iso

if [ "$bootloader" = "beef" ]; then
	if [ -e "beef" ]; then
		bootloader_location="boot/boot"

    dir=$(pwd)
		cd beef
		if [ -e "Makefile" ]; then
			make clean
			if [ -e "isofs" ]; then
				rm isofs # Just to make sure it's gone
			fi
			make
		else
			echo "WARNING: no Makefile for beef"
			bootloader=""
		fi
		if [ -e "isofs/boot" ]; then
			echo "beef built successfully"
			cp isofs/boot $dir/isofs/boot/boot
		else
			echo "WARNING: falling back to grub"
			bootloader=""
		fi
		cd $dir
	else
		echo "WARNING: beef does not exist, falling back to grub"
	fi
fi

if [ "$bootloader" = "" ]; then
	bootloader="grub"
fi


function grub(){
	echo $@ >> isofs/boot/grub/menu.lst
}

if [ "$bootloader" = "grub" ]; then
	bootloader_location="boot/grub/stage2_eltorito"

	mkdir -p isofs/boot/grub

	echo > isofs/boot/grub/menu.lst

	grub "default 1"
	grub "timeout 3"
	# metodo
	grub "title Metodo Dux"
	grub "kernel /System/metodo.exe"
	# metodo + userland
	grub "title Metodo Dux with Userland"
	grub "kernel /System/metodo.exe"
	grub "module /System/userland.exe"

	grub "title Metodo Dux with all modules (no userland)"
	grub "kernel /System/metodo.exe"
	for driver in $(cat drivers.tmp); do
		grub "module /Drivers/$driver"
	done

	grub "title Metodo Dux with all modules and Userland"
	grub "kernel /System/metodo.exe"
	grub "module /System/userland.exe"
	for driver in $(cat drivers.tmp); do
		grub "module /Drivers/$driver"
	done

	if [ ! -e 'isofs/boot/grub/stage2_eltorito' ]; then
		if [ -e /boot/grub/stage2_eltorito ]; then
			echo "Can't find stage2_eltorito in ./isofs/boot/grub, copying from /boot/grub/"
			cp /boot/grub/stage2_eltorito isofs/boot/grub/stage2_eltorito
		else
			#echo 'You need to locate stage2_eltorito and put it in ./isofs/boot/grub'
			#exit
			echo 'Downloading stage2_eltorito from http://misc.duckinator.net/stage2_eltorito'
			wget http://misc.duckinator.net/stage2_eltorito -O isofs/boot/grub/stage2_eltorito
		fi
	fi
fi

rm drivers.tmp

$isocmd -R -b $bootloader_location --no-emul-boot --boot-load-size 4 --boot-info-table --input-charset utf-8 -o iso/Dux.iso isofs
