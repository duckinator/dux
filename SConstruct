# vim: syntax=python

import os

arch = ARGUMENTS.get('arch', 'i386')
buildtype = ARGUMENTS.get('buildtype', 'debug')
ansi = ARGUMENTS.get('ansi', 'no')
strict = ARGUMENTS.get('strict', 'yes')
compiler = ARGUMENTS.get('compiler', 'clang')
linker = ARGUMENTS.get('linker', 'ld')
bootloader = ARGUMENTS.get('bootloader', 'grub')

os.system("./tools/buildid.sh > ./include/buildid.h \"%s\" \"%s\"" % (buildtype, arch))

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
	CCFLAGS=['-Wall', '-nostdinc', '-ffreestanding',  '-fno-stack-protector', '-fno-builtin', '-g', '-I', 'include', '-D', '%s' % arch.upper(), 
	         '-fdiagnostics-show-option', '-Wextra', '-Wunused', '-Wformat=2', '-Winit-self', '-Wmissing-include-dirs', '-Wstrict-overflow=4', '-Wfloat-equal',
	         '-Wwrite-strings', '-Wconversion', '-Wundef', '-Wtrigraphs', '-Wunused-parameter', '-Wunknown-pragmas', '-Wcast-align', '-Wswitch-enum',
	         '-Waggregate-return', '-Wmissing-noreturn', '-Wmissing-format-attribute', '-Wpacked', '-Wredundant-decls', '-Wunreachable-code', '-Winline',
	         '-Winvalid-pch', '-Wdisabled-optimization', '-Wsystem-headers', '-Wbad-function-cast'],
	AS='nasm',
	ASFLAGS=[],
	LINK='%s' % (linker),
	LINKFLAGS=['-nostdlib'],
	BUILDERS={'Iso': iso}
)

if arch == 'i386':
	env.Append(CCFLAGS=['-m32'], LINKFLAGS=['-melf_i386'], ASFLAGS=['-felf32'])
elif arch == 'x86_64':
	env.Append(CCFLAGS=['-m64'], LINKFLAGS=['-melf_x86_64'], ASFLAGS=['-felf64'])

# Add the following flags if clang is not the compiler used (it doesn't have them)
if env['CC'] != 'clang':
	env.Append(CCFLAGS=['-Wlogical-op', '-Wunsafe-loop-optimizations', '-Wpadded', '-Wstack-protector'])

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
