# This runs the floppy image in qemu with a ne2k ethernet card
qemu -net nic,ne2k -net user -fda image
