arch = 'x86'

default = Environment(
	CC='gcc',
	CCFLAGS=['-Iinclude/', '-nostdinc', '-m32'],
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

SConscript('src/kernel/SConscript', variant_dir='obj/kernel', duplicate=0)
