CC := clang
ASM := nasm
ARCH := i386
ARCHES := i386 x86_64
BUILD_TYPE := debug

#add all of these flags to whatever user input we get.
override CFLAGS += -m32 -Wall -nostdinc -ffreestanding  -fno-stack-protector -fno-builtin -g -I include -fdiagnostics-show-option -Wextra -Wunused -Wformat=2 -Winit-self -Wmissing-include-dirs -Wstrict-overflow=4 -Wfloat-equal -Wwrite-strings -Wconversion -Wundef -Wtrigraphs -Wunused-parameter -Wunknown-pragmas -Wcast-align -Wswitch-enum -Waggregate-return -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Wunreachable-code -Winline -Winvalid-pch -Wdisabled-optimization -Wsystem-headers -Wbad-function-cast

SOURCE_SUFFIXES := '(' -name '*.c' -o -name '*.asm' ')'
SRCFILES := $(shell find 'src' ${SOURCE_SUFFIXES})
ASMTARGETS = $(shell find 'src' -path '*/$(ARCH)/*' -name '*.asm' | sed 's/asm/o/g')
HDRFILES := $(shell find "src" -name "*.h")
OBJFILES := $(patsubst %.asm, %.o, $(patsubst %.c,%.o,$(SRCFILES)))
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))

CURARCHTARGETS := $(shell find 'src' '(' -path '*/${ARCH}/*' ')' '(' -name '*.c' -o -name '*.asm' ')' | sed 's/asm\|\bc/o/g')

# Eventually do this using ARCHES list, right now "just making it work"
ALLARCHTARGETS := $(shell find 'src' '(' -path '*/i386/*' -o -path '*/x86_64/*' ')' '(' -name '*.c' -o -name '*.asm' ')' | sed 's/asm\|\bc/o/g')

NOARCHTARGETS := ${filter-out ${ALLARCHTARGETS}, ${OBJFILES}}
objects := ${NOARCHTARGETS} ${CURARCHTARGETS}
BUILDINFO := $(shell ./tools/buildinfo.sh ${BUILD_TYPE} ${ARCH} > ./include/buildinfo.h)
all: Dux.exe

Dux.exe: metodo.exe
	@echo "it works"

metodo.exe: metodo-libs $(filter src/metodo/%, $(filter-out src/metodo/hal/% src/metodo/modules/%, ${objects}))
	ld -o src/metodo/metodo.exe -nostdlib -melf_i386 -g -T src/metodo/boot/i386/link.ld src/metodo/boot/i386/start.o $(filter-out metodo-libs src/metodo/boot/i386/start.o, $^) src/metodo/hal/i386/hal.lib src/lib/libc/libc.lib
	@echo $^

metodo-libs: hal.lib libc.lib user.exe vfs.lib

user.exe: krnllib.lib $(filter src/user/%.o, ${OBJFILES})
	ld -o src/user/user.exe -nostdlib -melf_i386 -g -Ttext 0x200000 $(sort $(filter src/user/%.o, ${OBJFILES})) -Lsrc/lib/krnllib src/lib/krnllib/krnllib.lib

hal.lib: $(filter src/metodo/hal/${ARCH}/%.o, ${OBJFILES})
	ar rc src/metodo/hal/${ARCH}/hal.lib $^
	ranlib src/metodo/hal/${ARCH}/hal.lib

#this needs to take advantage of static rules to apply for all of:
# <libname>: src/lib/<libname>/*.o
krnllib.lib: $(filter src/lib/krnllib/%.o, ${OBJFILES})
	ar rc src/lib/krnllib/krnllib.lib $^
	ranlib src/lib/krnllib/krnllib.lib

libc.lib: $(filter src/lib/libc/%.o, ${OBJFILES})
	ar rc src/lib/libc/libc.lib $^
	ranlib src/lib/libc/libc.lib

%.o: %.c
	@${CC} ${CFLAGS} -MMD -MP -MT "$*.d $*.o"  -c $< -o $@

#this needs to support more then 32bit by using if/else etc.
$(ASMTARGETS): %.o: %.asm
	${ASM} -f elf32 -o $@ $<

%::
	@echo "NOHIT" ${ARCH} '$$@' $@ '$$%' $% '$$<' $< '$$?' $? '$$^' $^ '$$+' $+ '$$|' $| '$$*' $*

clean:
	@find ./src -name '*.o' -delete
	@find ./src -name '*.lib' -delete
	@find ./src -name '*.exe' -delete

qemu: iso
	qemu -monitor stdio -cdrom iso/Dux.iso

iso: Dux.exe
	./makeiso.sh

test:
	@echo ${ALLARCHTARGETS}
	@echo ${NOARCHTARGETS}
	@echo ${CURARCHTARGETS}
	@echo ${objects}
