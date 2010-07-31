# vim: syntax=python

import os

os.system("./tools/buildid.sh > ./include/buildid.h")

arch = ARGUMENTS.get('arch', 'i386')
buildtype = ARGUMENTS.get('buildtype', 'debug')
ansi = ARGUMENTS.get('ansi', 'no')
strict = ARGUMENTS.get('strict', 'yes')
compiler = ARGUMENTS.get('compiler', 'clang')
linker = ARGUMENTS.get('linker', 'ld')
bootloader = ARGUMENTS.get('bootloader', 'grub')

iso = Builder(action='./makeiso.sh %s' % bootloader)

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
	CCFLAGS=['-Wall', '-m32', '-nostdinc', '-ffreestanding',  '-fno-stack-protector', '-fno-builtin', '-g', '-I', 'include', '-D', '%s' % arch.upper(),
	         '-Wextra', '-fdiagnostics-show-option', '-Wextra', '-Wunused', '-Wformat=2', '-Winit-self', '-Wmissing-include-dirs', '-Wstrict-overflow=4', '-Wfloat-equal',
	         '-Wwrite-strings', '-Wconversion', '-Wlogical-op', '-Wundef', '-Wunsafe-loop-optimizations', '-Wtrigraphs', '-Wunused-parameter', '-Wunknown-pragmas', '-Wcast-align',
	         '-Wswitch-enum', '-Waggregate-return', '-Wmissing-noreturn', '-Wmissing-format-attribute', '-Wpacked', '-Wpadded', '-Wredundant-decls', '-Wunreachable-code',
	         '-Winline', '-Winvalid-pch', '-Wdisabled-optimization', '-Wstack-protector'],
	AS='nasm',
	ASFLAGS=['-felf32'],
	LINK='%s' % (linker),
	LINKFLAGS=['-melf_i386', '-nostdlib'],
	BUILDERS={'Iso': iso}
)

if buildtype == 'debug':
	env.Append(CCFLAGS=['-g', '-D', 'DEBUG'], LINKFLAGS=['-g'])

if buildtype == 'syntax':
	env['LINK']='echo'
	env['LINKFLAGS']=[]
	if compiler == 'clang':
		env.Append(CCFLAGS=['--analyze'])
	elif compiler == 'gcc':
		env.Append(CCFLAGS=['-S'])

Export('env', 'arch', 'buildtype', 'distreq')

SConscript('src/SConscript')

if buildtype != 'syntax':
	env.Iso('iso/Dux.iso', distreq)
