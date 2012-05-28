#CC     :=clang
CC     := gcc
ASM    := nasm
AR     := ar
RANLIB := ranlib
LD     := ld

NAME= dux

BUILD_TYPE := debug

QEMU:= qemu-system-i386

SOURCE_SUFFIXES := '(' -name '*.c' -o -name '*.asm' ')'
SRCFILES := $(shell find 'src' ${SOURCE_SUFFIXES})
OBJFILES := $(patsubst %.asm,%.o,$(patsubst %.c,%.o,$(SRCFILES)))

#CFLAGS=-std=c99 -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -Iinclude -Iinclude/metodo -m32
override CFLAGS += -std=c99 -Wall -nostdinc -ffreestanding  -fno-stack-protector -fno-builtin -g -Iinclude -Iinclude/metodo -fdiagnostics-show-option -Wextra -Wunused -Wformat=2 -Winit-self -Wmissing-include-dirs -Wstrict-overflow=4 -Wfloat-equal -Wwrite-strings -Wconversion -Wundef -Wtrigraphs -Wunused-parameter -Wunknown-pragmas -Wcast-align -Wswitch-enum -Waggregate-return -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Wunreachable-code -Winline -Winvalid-pch -Wdisabled-optimization -Wsystem-headers -Wbad-function-cast -Wunused-function -m32

override LDFLAGS += -nostdlib -g -melf_i386

override ASFLAGS += -felf32


BUILDINFO := $(shell ./tools/buildinfo.sh ${BUILD_TYPE} x86_32 > ./include/buildinfo.h)

all: iso

metodo.exe: metodo-libs $(filter src/metodo/%, ${OBJFILES})
	${LD} -o src/metodo/metodo.exe ${LDFLAGS} -T src/metodo/boot/link.ld src/metodo/boot/start.o $(filter-out metodo-libs src/metodo/boot/start.o, $^) src/lib/libc/libc.lib
#	@echo $^

metodo-libs: libc.lib user.exe

user.exe: krnllib.lib $(filter src/user/%.o, ${OBJFILES})
	${LD} -o src/user/user.exe ${LDFLAGS} -Ttext 0x200000 $(sort $(filter src/user/%.o, ${OBJFILES})) -Lsrc/lib/krnllib src/lib/krnllib/krnllib.lib

#this needs to take advantage of static rules to apply for all of:
# <libname>: src/lib/<libname>/*.o
krnllib.lib: $(filter src/lib/krnllib/%.o, ${OBJFILES})
	${AR} rc src/lib/krnllib/krnllib.lib $^
	${RANLIB} src/lib/krnllib/krnllib.lib

libc.lib: $(filter src/lib/libc/%.o, ${OBJFILES})
	${AR} rc src/lib/libc/libc.lib $^
	${RANLIB} src/lib/libc/libc.lib


%.o: %.asm
	@#$(call STATUS,"ASSEMBLE",$^)
	${ASM} ${ASFLAGS} -o $@ $<

%.o: %.c
	@#$(call STATUS,"COMPILE ",$^)
	${CC} ${CFLAGS} -MMD -MP -MT "$*.d $*.o"  -c $< -o $@


iso: metodo.exe
	@#$(call STATUS,"Generating Dux.iso")
	@./makeiso.sh &> /dev/null
	@#$(call STATUS,"DONE")
	@#echo -e "Run one of the following to test:"
	@#echo -e "  ${COLOR_BLUE}make qemu${COLOR_RESET}"
	@#echo -e "  ${COLOR_BLUE}make qemu-monitor${COLOR_RESET}"
	@#echo -e "  ${COLOR_BLUE}make bochs${COLOR_RESET}"

test: iso
	@./test.sh "$(QEMU)"

qemu: test

clean:
	@find ./src -name '*.o'   -delete
	@find ./src -name '*.lib' -delete
	@find ./src -name '*.exe' -delete
	@find ./src -name '*.d'   -delete

.PHONY: all test qemu clean
