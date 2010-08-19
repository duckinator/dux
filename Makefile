COMPILER := clang
ARCH := I386 #default to 32 bit.

CCFLAGS := -m32 -Wall -nostdinc -ffreestanding  -fno-stack-protector -fno-builtin -g -I include -D${ARCH} -fdiagnostics-show-option -Wextra -Wunused -Wformat=2 -Winit-self -Wmissing-include-dirs -Wstrict-overflow=4 -Wfloat-equal -Wwrite-strings -Wconversion -Wundef -Wtrigraphs -Wunused-parameter -Wunknown-pragmas -Wcast-align -Wswitch-enum -Waggregate-return -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Wunreachable-code -Winline -Winvalid-pch -Wdisabled-optimization -Wsystem-headers -Wbad-function-cast

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
AOBJFILES := $(patsubst %.asm,%.o,$(ASMFILES))
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))

all: Dux.exe

Dux.exe: metodo.exe
	@echo ${OBJFILES_32}

%.o: %.c Makefile
	@${COMPILER} ${CCFLAGS} -MMD -MP -MT "$*.d $*.o"  -c $< -o $@

%.o: %.asm Makefile
	@nasm -f elf -o $@ $<

metodo.exe: ${OBJFILES_32} ${OBJFILES_NOT_ARCH_SPECIFIC}
	@ld -o src/metodo/metodo.exe -nostdlib -melf_i386 -g -T src/metodo/boot/i386/link.ld ${OBJFILES_32} ${OBJFILES_NOT_ARCH_SPECIFIC}

user.exe:
	@echo "user"

krnllib.lib:
	@echo "krnllib"

clean:
	@find ./src -name '*.o' -delete

iso: metodo.exe user.exe krnllib.lib
	./makeiso.sh