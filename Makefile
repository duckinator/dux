COMPILER := clang
#default to 32 bit.
ARCH := i386
ARCHES := i386 x86_64
BUILD_TYPE := debug

CCFLAGS := -m32 -Wall -nostdinc -ffreestanding  -fno-stack-protector -fno-builtin -g -I include -fdiagnostics-show-option -Wextra -Wunused -Wformat=2 -Winit-self -Wmissing-include-dirs -Wstrict-overflow=4 -Wfloat-equal -Wwrite-strings -Wconversion -Wundef -Wtrigraphs -Wunused-parameter -Wunknown-pragmas -Wcast-align -Wswitch-enum -Waggregate-return -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Wunreachable-code -Winline -Winvalid-pch -Wdisabled-optimization -Wsystem-headers -Wbad-function-cast

SRCFILES := $(shell find 'src' -name '*.c' -or -name '*.asm')
HDRFILES := $(shell find "src" -name "*.h")
SRCFILES_32 := $(shell find 'src' -path '*/i386/*' -a '(' -name '*.c' -o -name '*.asm' ')')
SRCFILES_64 := $(shell find 'src' -path '*/x86_64/*' -a '(' -name '*.c' -o -name '*.asm' ')')

SRCFILES_ARCH_SPECIFIC := ${SRCFILES_32} ${SRCFILES_64}

SRCFILES_NOT_ARCH_SPECIFIC := $(filter-out ${SRCFILES_ARCH_SPECIFIC}, ${SRCFILES})

OBJFILES_32 := $(patsubst %.asm, %.o, $(patsubst %.c,%.o,$(SRCFILES_32)))
OBJFILES_64 := $(patsubst %.asm, %.o, $(patsubst %.c,%.o,$(SRCFILES_64)))
OBJFILES_NOT_ARCH_SPECIFIC := $(patsubst %.asm, %.o, $(patsubst %.c,%.o,${SRCFILES_NOT_ARCH_SPECIFIC}))
OBJFILES := $(patsubst %.asm, %.o, $(patsubst %.c,%.o,$(SRCFILES)))
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))

ifeq (${ARCH},i386)
FINALOBJFILES := ${OBJFILES_32} ${OBJFILES_NOT_ARCH_SPECIFIC}
else ifeq (${ARCH}, x86_64)
FINALOBJFILES := ${OBJFILES_64} ${OBJFILES_NOT_ARCH_SPECIFIC}
else
$(error ${ARCH})
endif

BUILDINFO := $(shell ./tools/buildinfo.sh ${BUILD_TYPE} ${ARCH} > ./include/buildinfo.h)

all: Dux.exe

Dux.exe: hal.lib krnllib.lib vfs.lib
	@echo ${OBJFILES_32}

%.o: %.c Makefile
	@${COMPILER} ${CCFLAGS} -MMD -MP -MT "$*.d $*.o"  -c $< -o $@

%.o: %.asm Makefile
	@nasm -f elf -o $@ $<

hal.lib: $(filter src/metodo/hal/%, ${FINALOBJFILES})
	ar rc src/metodo/hal/i386/hal.lib $(filter src/metodo/hal/%, ${FINALOBJFILES})
	ranlib src/metodo/hal/i386/hal.lib

user.exe: krnllib.lib $(filter src/user/%, ${FINALOBJFILES})
	ld -o src/user/user.exe -nostdlib -melf_i386 -g -Ttext 0x200000 $(filter src/user/%, ${FINALOBJFILES}) -Lsrc/lib/krnllib src/lib/krnllib/krnllib.lib

krnllib.lib: $(filter src/lib/krnllib/%, ${FINALOBJFILES})
	ar rc src/lib/krnllib/krnllib.lib $(filter  src/lib/krnllib/%, ${FINALOBJFILES})
	ranlib src/lib/krnllib/krnllib.lib

vfs.lib: $(filter src/vfs/%, ${FINALOBJFILES})
	ar rc src/vfs/vfs.lib $(filter src/vfs/%, ${FINALOBJFILES})
	ranlib src/vfs/vfs.lib

clean:
	@find ./src -name '*.o' -delete

iso: Dux.exe
	./makeiso.sh

#@ld -o src/metodo/metodo.exe -nostdlib -melf_i386 -g -T src/metodo/boot/i386/link.ld ${OBJFILES_32} ${OBJFILES_NOT_ARCH_SPECIFIC}