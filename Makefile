include terminal.mk

NAME= dux

BUILD_TYPE := debug

QEMU:= qemu-system-i386

SOURCE_SUFFIXES := '(' -name '*.c' -o -name '*.asm' ')'
SRCFILES := $(shell find 'src' ${SOURCE_SUFFIXES})
OBJFILES := $(patsubst %.asm, %.o, $(patsubst %.c, %.o, $(SRCFILES)))

#CFLAGS=-std=c99 -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -Iinclude -Iinclude/kernel -m32
override CFLAGS += -std=c99 -Wall -nostdinc -ffreestanding  -fno-stack-protector -fno-builtin -g -Iinclude -Iinclude/kernel -fdiagnostics-show-option -Wextra -Wunused -Wformat=2 -Winit-self -Wmissing-include-dirs -Wstrict-overflow=4 -Wfloat-equal -Wwrite-strings -Wconversion -Wundef -Wtrigraphs -Wunused-parameter -Wunknown-pragmas -Wcast-align -Wswitch-enum -Waggregate-return -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Wunreachable-code -Winline -Winvalid-pch -Wdisabled-optimization -Wsystem-headers -Wbad-function-cast -Wunused-function -m32 -gdwarf-2 -pedantic-errors

override LDFLAGS += -nostdlib -g -melf_i386

override ASFLAGS += -felf32

include config.mk

BUILDINFO := $(shell ./tools/buildinfo.sh ${BUILD_TYPE} x86_32 > ./include/buildinfo.h)

all: config.mk iso
	@printf "${COLOR_GREEN}Run one of the following for debugging:${COLOR_RESET}\n"
	@printf "  ${COLOR_BLUE}make qemu${COLOR_RESET}\n"
	@printf "  ${COLOR_BLUE}make qemu-monitor${COLOR_RESET}\n"
	@printf "  ${COLOR_BLUE}make bochs${COLOR_RESET}\n"
	@echo
	@printf "${COLOR_GREEN}Run the following to run the test suite:${COLOR_RESET}\n"
	@printf "  ${COLOR_BLUE}make test${COLOR_RESET}\n"

config.mk:
	@printf "You will need to copy config.mk.dist to config.mk first."
	@false

kernel.exe: kernel-libs $(filter src/kernel/%, ${OBJFILES})
	@${LD} -o src/kernel/kernel.exe ${LDFLAGS} -T src/kernel/boot/link.ld src/kernel/boot/start.o $(filter-out kernel-libs src/kernel/boot/start.o, $^) src/lib/libc/libc.lib
#	@/bin/echo $^

kernel-libs: libc.lib userland.exe

userland.exe: krnllib.lib libc.lib $(filter src/userland/%.o, ${OBJFILES})
	@${LD} -o src/userland/userland.exe ${LDFLAGS} -Ttext 0x200000 $(sort $(filter src/userland/%.o, ${OBJFILES})) -Lsrc/lib/krnllib src/lib/krnllib/krnllib.lib -Lsrc/lib/libc src/lib/libc/libc.lib

#this needs to take advantage of static rules to apply for all of:
# <libname>: src/lib/<libname>/*.o
krnllib.lib: $(filter src/lib/krnllib/%.o, ${OBJFILES})
	@${AR} rc src/lib/krnllib/krnllib.lib $^
	@${RANLIB} src/lib/krnllib/krnllib.lib

libc.lib: $(filter src/lib/libc/%.o, ${OBJFILES})
	@${AR} rc src/lib/libc/libc.lib $^
	@${RANLIB} src/lib/libc/libc.lib

hal.lib: $(filter src/kernel/hal/%.o, ${OBJFILES})
	@${AR} rc  src/kernel/hal/hal.lib $^
	@${RANLIB} src/kernel/hal/hal.lib


-include $(find ./src -name '*.d')
%.o: %.c
	@$(call STATUS,"COMPILE ",$^)
	@${CC} ${CFLAGS} -MMD -MP -MT "$*.d $*.o"  -c $< -o $@

%.o: %.asm
	@$(call STATUS,"ASSEMBLE",$^)
	@${ASM} ${ASFLAGS} -o $@ $<

include modules.mk

tools/bootinfo: tools/bootinfo.c
	cc -o $@ $<

#iso: tools/bootinfo kernel.exe modules
iso: tools/bootinfo kernel.exe
	@$(call STATUS,"Generating Dux.iso")
	@./makeiso.sh
	@$(call STATUS,"DONE")

test: iso
	@./test.sh "$(QEMU)"

qemu: iso
	qemu-system-i386 -vga std -serial stdio -cdrom iso/dux.iso

qemu-monitor: iso
	qemu-system-i386 -monitor stdio -cdrom iso/dux.iso

bochs: iso
	./run.sh

vbox: iso
	VirtualBox --startvm dux --debug-statistics --debug-command-line --start-running

todo:
	@./tools/todo.sh

sloc:
	@sloccount ./src ./include | grep "(SLOC)"

clean:
	@find ./src -name '*.o'   -delete
	@find ./src -name '*.lib' -delete
	@find ./src -name '*.exe' -delete
	@find ./src -name '*.d'   -delete
	@rm -f tools/bootinfo

.PHONY: all kernel-libs iso clean test qemu qemu-monitor bochs todo sloc clean
