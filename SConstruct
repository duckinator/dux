# vim: syntax=python

import os

os.system("./tools/buildid.sh > ./include/buildid.h")

arch = ARGUMENTS.get('arch', 'i386')
buildtype = ARGUMENTS.get('buildtype', 'debug')
ansi = ARGUMENTS.get('ansi', 'no')
strict = ARGUMENTS.get('strict', 'yes')
compiler = ARGUMENTS.get('compiler', 'i386-elf-gcc')
linker = ARGUMENTS.get('linker', 'i386-elf-ld')

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
	CCFLAGS=['-nostdinc', '-fno-builtin', '-g', '-I', 'include', '-I', 'include/arch/%s' % arch, '-D', '%s' % arch.upper()],
	AS='nasm',
	ASFLAGS=['-felf32'],
	LINK='%s' % (linker),
	LINKFLAGS=['-nostdlib'],
	AR='i386-elf-ar',
	RANLIB='i386-elf-ranlib',
	BUILDERS={'Iso': iso}
)

if buildtype == 'debug':
	env.Append(CCFLAGS=['-g', '-D', 'DEBUG'], LINKFLAGS=['-g'])

Export('env', 'arch', 'buildtype', 'distreq')

SConscript('src/SConscript')

env.Iso('iso/Dux.iso', distreq)
