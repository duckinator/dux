arch = 'x86'

default = Environment(
	CC='gcc',
	CCFLAGS=['-nostdinc', '-m32'],
        CPPPATH = ['#include','#include-MAKE'],
	AS='nasm',
	ASFLAGS=['-felf32'],
	LINK='ld',
	LINKFLAGS=['-melf_i386', '-nostdlib']
)

debug = default.Clone()
debug.Append(CCFLAGS=['-g'])
debug.Append(ASFLAGS=['-gstabs'])
debug.Append(LINKFLAGS=['-g'])

env = debug

Export('env', 'arch')

SConscript('src/userland/SConscript')
SConscript('src/kernel/SConscript',  duplicate=0)

