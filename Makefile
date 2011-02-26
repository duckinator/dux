CC := clang
ASM := nasm
ARCH := i386
ARCHES := i386 amd64
BUILD_TYPE := debug

# Add all of these flags to whatever user input we get.
override CFLAGS += -std=c99 -Wall -nostdinc -ffreestanding  -fno-stack-protector -fno-builtin -g -I include -fdiagnostics-show-option -Wextra -Wunused -Wformat=2 -Winit-self -Wmissing-include-dirs -Wstrict-overflow=4 -Wfloat-equal -Wwrite-strings -Wconversion -Wundef -Wtrigraphs -Wunused-parameter -Wunknown-pragmas -Wcast-align -Wswitch-enum -Waggregate-return -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Wunreachable-code -Winline -Winvalid-pch -Wdisabled-optimization -Wsystem-headers -Wbad-function-cast -Wunused-function

override LDFLAGS += -nostdlib -g

# May we well place this here in case it's needed later
#override ASFLAGS +=

ifeq "${ARCH}" "i386"
	override CFLAGS += -m32
	override LDFLAGS += -melf_i386
	override ASFLAGS += -felf32
else
	ifeq "${ARCH}" "amd64"
		override CFLAGS += -m64
		override LDFLAGS += -melf_x86_64
		override ASFLAGS += -felf64
	endif
endif

SOURCE_SUFFIXES := '(' -name '*.c' -o -name '*.asm' ')'
SRCFILES := $(shell find 'src' ${SOURCE_SUFFIXES})
ASMTARGETS = $(shell find 'src' -path '*/$(ARCH)/*' -name '*.asm' | sed 's/asm/o/g')
HDRFILES := $(shell find "src" -name "*.h")
OBJFILES := $(patsubst %.asm, %.o, $(patsubst %.c,%.o,$(SRCFILES)))
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))

CURARCHTARGETS := $(shell find 'src' '(' -path '*/${ARCH}/*' ')' '(' -name '*.c' -o -name '*.asm' ')' | sed 's/asm\|\bc/o/g')

# Eventually do this using ARCHES list, right now "just making it work"
ALLARCHTARGETS := $(shell find 'src' '(' -path '*/i386/*' -o -path '*/amd64/*' ')' '(' -name '*.c' -o -name '*.asm' ')' | sed 's/asm\|\bc/o/g')

NOARCHTARGETS := ${filter-out ${ALLARCHTARGETS}, ${OBJFILES}}
objects := ${NOARCHTARGETS} ${CURARCHTARGETS}
BUILDINFO := $(shell ./tools/buildinfo.sh ${BUILD_TYPE} ${ARCH} > ./include/buildinfo.h)
all: iso

metodo.exe: metodo-libs $(filter src/metodo/%, $(filter-out src/metodo/hal/% src/metodo/modules/%, ${objects}))
	ld -o src/metodo/metodo.exe ${LDFLAGS} -T src/metodo/${ARCH}/boot/link.ld src/metodo/${ARCH}/boot/start.o $(filter-out metodo-libs src/metodo/${ARCH}/boot/start.o, $^) src/metodo/${ARCH}/hal/hal.lib src/lib/libc/libc.lib
	@echo $^

metodo-libs: hal.lib libc.lib user.exe

user.exe: krnllib.lib $(filter src/user/%.o, ${OBJFILES})
	ld -o src/user/user.exe ${LDFLAGS} -Ttext 0x200000 $(sort $(filter src/user/%.o, ${OBJFILES})) -Lsrc/lib/krnllib src/lib/krnllib/krnllib.lib

hal.lib: $(filter src/metodo/${ARCH}/hal/%.o, ${OBJFILES})
	ar rc src/metodo/${ARCH}/hal/hal.lib $^
	ranlib src/metodo/${ARCH}/hal/hal.lib

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

$(ASMTARGETS): %.o: %.asm
	${ASM} ${ASFLAGS} -o $@ $<

%::
	@echo "NOHIT" ${ARCH} '$$@' $@ '$$%' $% '$$<' $< '$$?' $? '$$^' $^ '$$+' $+ '$$|' $| '$$*' $*

clean:
	@find ./src -name '*.o' -delete
	@find ./src -name '*.lib' -delete
	@find ./src -name '*.exe' -delete

qemu: iso
	qemu -monitor stdio -cdrom iso/Dux.iso

iso: metodo.exe
	./makeiso.sh

test:
	@echo ${ALLARCHTARGETS}
	@echo ${NOARCHTARGETS}
	@echo ${CURARCHTARGETS}
	@echo ${objects}
