# vim: syntax=python

arch = ARGUMENTS.get('arch', 'x86')
buildtype = ARGUMENTS.get('buildtype', 'debug')
ansi = ARGUMENTS.get('ansi', 'no')

env = Environment(
	CC='gcc',
	CCFLAGS=['-nostdinc', '-m32', '-I', 'include', '-I', 'include/arch/%s' % arch],
	AS='nasm',
	ASFLAGS=['-felf32'],
	LINK='ld',
	LINKFLAGS=['-melf_i386', '-nostdlib']
)

if buildtype == 'debug':
	env.Append(CCFLAGS=['-g'], LINKFLAGS=['-g'])

if ansi == 'yes':
	env.Append(CCFLAGS=['-ansi'])

Export('env', 'arch', 'buildtype')

SConscript('user/SConscript')
SConscript('krnl/SConscript')
