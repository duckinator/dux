# vim: syntax=python

import os

os.system("./tools/buildid.sh > ./include/buildid.h")

arch = ARGUMENTS.get('arch', 'i386')
buildtype = ARGUMENTS.get('buildtype', 'debug')
ansi = ARGUMENTS.get('ansi', 'no')
strict = ARGUMENTS.get('strict', 'yes')
compiler = ARGUMENTS.get('compiler', 'clang')
linker = ARGUMENTS.get('linker', 'ld')

iso = Builder(action='./makeiso.sh')

distreq = []

env = Environment(
	ENV = {'PATH' : os.environ['PATH']},
	OBJPREFIX='',
	OBJSUFFIX='.o',
	SHOBJPREFIX='',
	SHOBJSUFFIX='.sho',
	PROGPREFIX='',
	PROGSUFFIX='.exe',
	LIBPREFIX='',
	LIBSUFFIX='.lib',
	SHLIBPREFIX='',
	SHLIBSUFFIX='.shl',
	CC='%s' % (compiler),
	CCFLAGS=['-m32', '-nostdinc', '-ffreestanding',  '-fno-stack-protector', '-fno-builtin', '-g', '-I', 'include', '-I', 'include/arch/%s' % arch, '-D', '%s' % arch.upper()],
	AS='nasm',
	ASFLAGS=['-felf32'],
	LINK='%s' % (linker),
	LINKFLAGS=['-melf_i386', '-nostdlib'],
	BUILDERS={'Iso': iso}
)

if buildtype == 'debug':
	env.Append(CCFLAGS=['-g', '-D', 'DEBUG'], LINKFLAGS=['-g'])

Export('env', 'arch', 'buildtype', 'distreq')

SConscript('src/SConscript')

env.Iso('iso/Dux.iso', distreq)
