# dux

Dux is an operating system started in 2008, and was mostly unmaintained from 2012 to 2014. It's a hot mess.

**NOTE:** If you cloned this repository before July 11th 2017, you will
need to re-clone it. I (@duckinator) modified the commit history to
correct my name.

## Requirements

To compile dux you need:

* GNU Make
* A C compiler (clang is officially supported, gcc should work)
* nasm (assembler)
* ld (any linker which can link an elf binary should work)
* genisoimage (or mkisofs)

It should compile on most UNIX-y systems, assuming the above dependencies are met. In theory.

## Compiling

```
$ cp config.mk.dist config.mk
# Edit config.mk, if necessary
$ make
```

## Licensing

Released under the MIT license, see LICENSE for more information.
