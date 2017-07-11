#modules: kernel.exe test_module.exe uart.exe
modules: kernel.exe
	@mkdir -p isofs/Modules
	./copymodules.sh

test_module.exe: krnllib.lib libc.lib src/modules/test_module/test_module.o
	@${LD} -o src/modules/test_module/test_module.exe ${LDFLAGS} -Ttext 0x200000 src/modules/test_module/test_module.o -Lsrc/lib/krnllib src/lib/krnllib/krnllib.lib -Lsrc/lib/libc src/lib/libc/libc.lib

uart.exe: krnllib.lib libc.lib hal.lib src/modules/uart/uart.o
	@${LD} -o src/modules/uart/uart.exe ${LDFLAGS} -Ttext 0x200000 src/modules/uart/uart.o -Lsrc/lib/krnllib src/lib/krnllib/krnllib.lib -Lsrc/lib/libc src/lib/libc/libc.lib -Lsrc/kernel/hal src/kernel/hal/hal.lib
