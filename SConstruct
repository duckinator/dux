# vim: syntax=python

import os

os.system("python ./tools/buildid.py > ./include/buildid.h")
os.system("cd ./tools/initrd/ && make && cd -")

arch = ARGUMENTS.get('arch', 'i386')
buildtype = ARGUMENTS.get('buildtype', 'debug')
ansi = ARGUMENTS.get('ansi', 'no')
strict = ARGUMENTS.get('strict', 'yes')

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
	CC='i386-dux-pcc',
	CCFLAGS=['-nostdinc', '-g', '-I', 'include', '-I', 'include/arch/%s' % arch, '-D', '%s' % arch.upper()],
	AS='nasm',
	ASFLAGS=['-felf32'],
	LINK='i386-dux-ld',
	LINKFLAGS=['-nostdlib'],
	BUILDERS={'Iso': iso}
)

if buildtype == 'debug':
	env.Append(CCFLAGS=['-g', '-D', 'DEBUG'], LINKFLAGS=['-g'])

Export('env', 'arch', 'buildtype', 'distreq')

SConscript('src/SConscript')

env.Iso('iso/Dux.iso', distreq)
