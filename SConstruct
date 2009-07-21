# vim: syntax=python

import os

arch = ARGUMENTS.get('arch', 'x86')
buildtype = ARGUMENTS.get('buildtype', 'debug')
ansi = ARGUMENTS.get('ansi', 'no')
strict = ARGUMENTS.get('strict', 'yes')

iso = Builder(action='./makeiso.sh')

env = Environment(
	CC='gcc',
	CCFLAGS=['-m32', '-nostdinc', '-ffreestanding', '-I', 'include', '-I', 'include/arch/%s' % arch],
	AS='nasm',
	ASFLAGS=['-felf32'],
	LINK='ld',
	LINKFLAGS=['-melf_i386', '-nostdlib'],
	BUILDERS={'Iso': iso}
)

if buildtype == 'debug':
	env.Append(CCFLAGS=['-g', '-DDEBUG'], LINKFLAGS=['-g'])

if ansi == 'yes':
	env.Append(CCFLAGS=['-ansi'])

if strict == 'yes':
	env.Append(CCFLAGS=['-Werror'])

Export('env', 'arch', 'buildtype')

SConscript('user/SConscript')
SConscript('krnl/SConscript')

env.Iso('Dux.iso', 'krnl/krnl')
