#!/bin/sh

        mkdir -p isofiles/boot/grub
        cp ./tools/stage2_eltorito ./isofiles/boot/grub
        cp ./src/kernel/kernel ./isofiles/boot/dux
        touch ./isofiles/boot/grub/menu.lst
        echo "default 0" >> ./isofiles/boot/grub/menu.lst
        echo "timeout 1" >> ./isofiles/boot/grub/menu.lst
        echo "title Dux" >> ./isofiles/boot/grub/menu.lst
        echo "kernel /boot/dux" >> ./isofiles/boot/grub/menu.lst
        echo "module /boot/dux" >> ./isofiles/boot/grub/menu.lst
        genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o Dux.iso isofiles
	rm -r isofiles/
