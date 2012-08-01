# TODO: Make this not have to manually specify each module...

modules: metodo.exe test_module.exe serial.exe
	@mkdir -p isofs/Modules
	@cp src/modules/test_module.exe isofs/Modules/

test_module.exe: krnllib.lib libc.lib src/modules/test_module.o
	@${LD} -o src/modules/test_module.exe ${LDFLAGS} -Ttext 0x200000 src/modules/test_module.o -Lsrc/lib/krnllib src/lib/krnllib/krnllib.lib -Lsrc/lib/libc src/lib/libc/libc.lib

serial.exe: krnllib.lib libc.lib hal.lib src/modules/serial.o
	@${LD} -o src/modules/serial.exe ${LDFLAGS} -Ttext 0x200000 src/modules/serial.o -Lsrc/lib/krnllib src/lib/krnllib/krnllib.lib -Lsrc/lib/libc src/lib/libc/libc.lib -Lsrc/metodo/hal src/metodo/hal/hal.lib
