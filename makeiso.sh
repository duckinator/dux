#!/bin/sh


function error() {
	echo "ERROR: ${@}"
	exit 1
}

bootloader="$1"

downloadcmd=""
which wget > /dev/null
if [ $? -eq 0 ]; then
	downloadcmd="wget"
else
    # No wget, try curl
    which curl > /dev/null
    if [ $? -eq 1 ]; then
    	error "You need to have curl or wget installed."
    else
    	downloadcmd="curl"
    fi
fi

isocmd=""
which genisoimage > /dev/null
if [ $? -eq 0 ]; then
	isocmd="genisoimage"
else
	which mkisofs > /dev/null
	if [ $? -eq 0 ]; then
		isocmd="mkisofs"
	else
		error "You need to have genisoimage or mkisofs installed."
	fi
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

if [ -e "isofs/Modules" ]; then
	rm -r isofs/Modules
fi

mkdir -p isofs/System
mkdir -p isofs/Drivers
mkdir -p isofs/Modules
mkdir -p isofs/boot

cp src/metodo/metodo.exe isofs/System/
cp src/user/user.exe isofs/System/userland.exe
cp src/lib/krnllib/krnllib.lib isofs/System/

function handle_modules() {
	TYPE="$1"
	DIR="$2"
	ESC_DIR=$(echo $DIR | sed 's/\//\\\//g')
	#echo > $TYPE.tmp
	for f in $(ls $2/*.exe); do
		filename=$(echo $f | sed 's/${ESC_DIR}//')
		cp "$f" "isofs/${TYPE}/${filename}"
		echo $filename >> $TYPE.tmp
	done
}

echo > Drivers.tmp
#for f in $(ls src/metodo/modules/driver/*/*.exe); do
#	filename=$(echo $f | sed "s/src\/metodo\/driver\/.*\///")
#	cp "$f" "isofs/Drivers/$filename"
#	echo "$filename" >> drivers.tmp
#done

handle_modules "Drivers" "src/metodo/modules/driver/*/"

echo > Modules.tmp
for x in $(ls src/metodo/modules); do
	handle_modules "Modules" "src/metodo/modules/${x}/*"
done
#for f in $(ls src/metodo/modules/*/*.exe); do
#	filename=$(echo $f | sed "s/src\/metodo\/driver\/.*\///")
#	cp "$f" "isofs/Drivers/$filename"
#	echo "$filename" >> drivers.tmp
#done

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
	for driver in $(cat Drivers.tmp); do
		grub "module /Drivers/$driver"
	done
	for module in $(cat Modules.tmp); do
		grub "module /Modules/$module"
	done

	grub "title Metodo Dux with all modules and Userland"
	grub "kernel /System/metodo.exe"
	grub "module /System/userland.exe"
	for driver in $(cat Drivers.tmp); do
		grub "module /Drivers/$driver"
	done
	for module in $(cat Modules.tmp); do
		grub "module /Modules/$module"
	done

	if [ ! -e isofs/boot/grub/stage2_eltorito ]; then
		if [ -e /boot/grub/stage2_eltorito ]; then
			echo "Can't find stage2_eltorito in ./isofs/boot/grub, copying from /boot/grub/"
			cp /boot/grub/stage2_eltorito isofs/boot/grub/stage2_eltorito
		else
			echo "Downloading stage2_eltorito from http://misc.duckinator.net/stage2_eltorito"
			cd isofs/boot/grub/
			$downloadcmd http://misc.duckinator.net/stage2_eltorito -O stage2_eltorito
			cd -
		fi
	fi
fi

rm Drivers.tmp Modules.tmp

$isocmd -R -b $bootloader_location --no-emul-boot --boot-load-size 4 --boot-info-table --input-charset utf-8 -o iso/Dux.iso isofs
