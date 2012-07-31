modules: test_module.exe
	@mkdir -p isofs/Modules
	@cp src/modules/test_module.exe isofs/Modules/

test_module.exe: krnllib.lib libc.lib src/modules/test_module.o
	@${LD} -o src/modules/test_module.exe ${LDFLAGS} -Ttext 0x200000 src/modules/test_module.o -Lsrc/lib/krnllib src/lib/krnllib/krnllib.lib -Lsrc/lib/libc src/lib/libc/libc.lib

