# vim: syntax=python

arch = ARGUMENTS.get('arch', 'x86')
buildtype = ARGUMENTS.get('buildtype', 'debug')
ansi = ARGUMENTS.get('ansi', 'no')
strict = ARGUMENTS.get('strict', 'yes')

env = Environment(
	CC='gcc',
	CCFLAGS=['-m32', '-nostdinc', '-ffreestanding', '-I', 'include', '-I', 'include/arch/%s' % arch],
	AS='nasm',
	ASFLAGS=['-felf32'],
	LINK='ld',
	LINKFLAGS=['-melf_i386', '-nostdlib']
)

if buildtype == 'debug':
	env.Append(CCFLAGS=['-g'], LINKFLAGS=['-g'])

if ansi == 'yes':
	env.Append(CCFLAGS=['-ansi'])

if strict == 'yes':
	env.Append(CCFLAGS=['-Werror'])

Export('env', 'arch', 'buildtype')

SConscript('user/SConscript')
SConscript('krnl/SConscript')
