all: make_initrd initrd.img

make_initrd:
	(gcc -o make_initrd make_initrd.c)

initrd.img: make_initrd
	(cd sample_files && ../make_initrd one two three; mv ./initrd.img ..)

clean:
	rm make_initrd

.PHONY: all initrd.img clean

