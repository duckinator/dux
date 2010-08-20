CC := clang
ASM := nasm
ARCH := i386
BUILD_TYPE := debug

#add all of these flags to whatever user input we get.
override CFLAGS += -m32 -Wall -nostdinc -ffreestanding  -fno-stack-protector -fno-builtin -g -I include -fdiagnostics-show-option -Wextra -Wunused -Wformat=2 -Winit-self -Wmissing-include-dirs -Wstrict-overflow=4 -Wfloat-equal -Wwrite-strings -Wconversion -Wundef -Wtrigraphs -Wunused-parameter -Wunknown-pragmas -Wcast-align -Wswitch-enum -Waggregate-return -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Wunreachable-code -Winline -Winvalid-pch -Wdisabled-optimization -Wsystem-headers -Wbad-function-cast

SRCFILES := $(shell find 'src' ${SOURCE_SUFFIXES})
HDRFILES := $(shell find "src" -name "*.h")
OBJFILES := $(patsubst %.asm, %.o, $(patsubst %.c,%.o,$(SRCFILES)))
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))

BUILDINFO := $(shell ./tools/buildinfo.sh ${BUILD_TYPE} ${ARCH} > ./include/buildinfo.h)

all: Dux.exe

Dux.exe: metodo.exe
	@echo "it works"

metodo.exe: hal.lib

hal.lib: $(filter src/metodo/hal/${ARCH}/%o, ${OBJFILES})
	ar rc src/metodo/hal/i386/hal.lib $+
	ranlib src/metodo/hal/i386/hal.lib

%.o: %.c
	@${CC} ${CFLAGS} -MMD -MP -MT "$*.d $*.o"  -c $< -o $@

%.o: %.asm
	@${ASM} -f elf -o $@ $<

%::
	@echo "NOHIT" $(dall)

#print out all the cool info in special variables (debug only)
define dall
@echo '$$@' $@ '$$%' $% '$$<' $< '$$?' $? '$$^' $^ '$$+' $+ '$$|' $| '$$*' $*
endef