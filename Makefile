include terminal.mk

CC     := clang
ASM    := nasm
AR     := ar
RANLIB := ranlib
LD     := ld

ARCH := i386
ARCHES := i386 amd64
BUILD_TYPE := debug

# Add all of these flags to whatever user input we get.
override CFLAGS += -std=c99 -Wall -nostdinc -ffreestanding  -fno-stack-protector -fno-builtin -g -I include -fdiagnostics-show-option -Wextra -Wunused -Wformat=2 -Winit-self -Wmissing-include-dirs -Wstrict-overflow=4 -Wfloat-equal -Wwrite-strings -Wconversion -Wundef -Wtrigraphs -Wunused-parameter -Wunknown-pragmas -Wcast-align -Wswitch-enum -Waggregate-return -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Wunreachable-code -Winline -Winvalid-pch -Wdisabled-optimization -Wsystem-headers -Wbad-function-cast -Wunused-function

override LDFLAGS += -nostdlib -g

# May we well place this here in case it's needed later
#override ASFLAGS +=

SOURCE_SUFFIXES := '(' -name '*.c' -o -name '*.asm' ')'
SRCFILES := $(shell find 'src' ${SOURCE_SUFFIXES})
ASMTARGETS = $(patsubst %.asm, %.o, $(shell find 'src' -path '*/$(ARCH)/*' -name '*.asm'))
HDRFILES := $(shell find "src" -name "*.h")
OBJFILES := $(patsubst %.asm, %.o, $(patsubst %.c,%.o,$(SRCFILES)))
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))

CURARCHTARGETS := $(patsubst %.asm, %.o, $(patsubst %.c, %.o, $(shell find 'src' '(' -path '*/${ARCH}/*' ')' '(' -name '*.c' -o -name '*.asm' ')')))

X86TARGETS := $(patsubst %.asm, %.o, $(patsubst %.c, %.o, $(shell find 'src' '(' -path '*/x86/*' ')' '(' -name '*.c' -o -name '*.asm' ')')))

# Eventually do this using ARCHES list, right now "just making it work"
ALLARCHTARGETS := $(patsubst %.asm, %.o, $(patsubst %.c, %.o, $(shell find 'src' '(' -path '*/i386/*' -o -path '*/amd64/*' -o -path '*/x86/*' ')' '(' -name '*.c' -o -name '*.asm' ')')))

NOARCHTARGETS := ${filter-out ${ALLARCHTARGETS}, ${OBJFILES}}
objects := ${NOARCHTARGETS} ${CURARCHTARGETS}
BUILDINFO := $(shell ./tools/buildinfo.sh ${BUILD_TYPE} ${ARCH} > ./include/buildinfo.h)

ifeq "${ARCH}" "i386"
	override CFLAGS += -m32
	override LDFLAGS += -melf_i386
	override ASFLAGS += -felf32
	override objects += ${X86TARGETS}
else
	ifeq "${ARCH}" "amd64"
		override CFLAGS += -m64
		override LDFLAGS += -melf_x86_64
		override ASFLAGS += -felf64
		override objects += ${X86TARGETS}
	endif
endif

# "terminalfix" is required so it wont overwrite your prompt.
# Would be nice if this could somehow be handled inside of terminal.mk,
# to remove as much terminal-specific clutter as possible
all: terminalfix iso

terminalfix:
	@echo # Don't overwrite the prompt :P

metodo.exe: metodo-libs $(filter src/metodo/%, $(filter-out src/metodo/hal/% src/metodo/modules/%, ${objects}))
	@${LD} -o src/metodo/metodo.exe ${LDFLAGS} -T src/metodo/${ARCH}/boot/link.ld src/metodo/${ARCH}/boot/start.o $(filter-out metodo-libs src/metodo/${ARCH}/boot/start.o, $^) src/metodo/${ARCH}/hal/hal.lib src/lib/libc/libc.lib
#	@echo $^

metodo-libs: hal.lib libc.lib user.exe

user.exe: krnllib.lib $(filter src/user/%.o, ${OBJFILES})
	@${LD} -o src/user/user.exe ${LDFLAGS} -Ttext 0x200000 $(sort $(filter src/user/%.o, ${OBJFILES})) -Lsrc/lib/krnllib src/lib/krnllib/krnllib.lib

hal.lib: $(filter src/metodo/${ARCH}/hal/%.o, ${OBJFILES})
	@${AR} rc src/metodo/${ARCH}/hal/hal.lib $^
	@${RANLIB} src/metodo/${ARCH}/hal/hal.lib

#this needs to take advantage of static rules to apply for all of:
# <libname>: src/lib/<libname>/*.o
krnllib.lib: $(filter src/lib/krnllib/%.o, ${OBJFILES})
	@${AR} rc src/lib/krnllib/krnllib.lib $^
	@${RANLIB} src/lib/krnllib/krnllib.lib

libc.lib: $(filter src/lib/libc/%.o, ${OBJFILES})
	@${AR} rc src/lib/libc/libc.lib $^
	@${RANLIB} src/lib/libc/libc.lib

-include $(find ./src -name '*.d')
%.o: %.c
	@$(call STATUS,"COMPILE",$^)
	@${CC} ${CFLAGS} -MMD -MP -MT "$*.d $*.o"  -c $< -o $@

$(ASMTARGETS): %.o: %.asm
	@$(call STATUS,"ASSEMBLE",$^)
	@${ASM} ${ASFLAGS} -o $@ $<

#%::
#	@echo "NOHIT" ${ARCH} '$$@' $@ '$$%' $% '$$<' $< '$$?' $? '$$^' $^ '$$+' $+ '$$|' $| '$$*' $*

clean:
	@find ./src -name '*.o'   -delete
	@find ./src -name '*.lib' -delete
	@find ./src -name '*.exe' -delete
	@find ./src -name '*.d'   -delete

qemu: iso
	qemu -serial stdio -cdrom iso/Dux.iso

qemu-monitor: iso
	qemu -monitor stdio -cdrom iso/Dux.iso

bochs: iso
	./run.sh

iso: metodo.exe
	@$(call STATUS,"Generating Dux.iso")
	@./makeiso.sh &> /dev/null
	@$(call STATUS,"DONE")
	@echo -e "Run one of the following to test:"
	@echo -e "  ${COLOR_BLUE}make qemu${COLOR_RESET}"
	@echo -e "  ${COLOR_BLUE}make qemu-monitor${COLOR_RESET}"
	@echo -e "  ${COLOR_BLUE}make bochs${COLOR_RESET}"

todo:
	@./tools/todo.sh

sloc:
	@sloccount ./src ./include | grep "(SLOC)"

test:
	@echo ${ALLARCHTARGETS}
	@echo ${NOARCHTARGETS}
	@echo ${CURARCHTARGETS}
	@echo ${objects}

.PHONY: terminalfix metodo-libs iso clean qemu qemu-monitor bochs todo sloc
