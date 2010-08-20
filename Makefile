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

#what depends on vfs.lib?
metodo.exe: hal.lib user.exe vfs.lib

user.exe: krnllib.lib $(filter src/user/%.o, ${OBJFILES})

hal.lib: $(filter src/metodo/hal/${ARCH}/%.o, ${OBJFILES})
	ar rc src/metodo/hal/${ARCH}/hal.lib $^
	ranlib src/metodo/hal/${ARCH}/hal.lib

#this needs to take advantage of static rules to apply for all of:
# <libname>: src/lib/<libname>/*.o
krnllib.lib: $(filter src/lib/krnllib/%.o, ${OBJFILES})
	ar rc src/lib/krnllib/krnllib.lib $^
	ranlib src/lib/krnllib/krnllib.lib

#duck says this is going away, if he is smart, he puts it in src/lib/vfs/ or similar.
vfs.lib: $(filter src/vfs/%.o, ${OBJFILES})
	ar rc src/vfs/vfs.lib $+
	ranlib src/vfs/vfs.lib

%.o: %.c
	@${CC} ${CFLAGS} -MMD -MP -MT "$*.d $*.o"  -c $< -o $@

%.o: %.asm
	@${ASM} -f elf -o $@ $<

%::
	@echo "NOHIT" '$$@' $@ '$$%' $% '$$<' $< '$$?' $? '$$^' $^ '$$+' $+ '$$|' $| '$$*' $*