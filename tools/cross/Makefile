# For OS X, use binutils 2.18 and gcc 4.2.4
BINUTILS_VERSION=2.20.1
GCC_VERSION=4.4.3
TARGET=i386-elf
PREFIX=$(HOME)/duxcc
DOWNLOADS=downloads
BINDIR=$(PREFIX)/bin
INCDIR=$(PREFIX)/includes
LIBDIR=$(PREFIX)/libs

all: pre binutils

pre:
	mkdir -p $(DOWNLOADS)
	mkdir -p $(PREFIX)
	mkdir -p $(BINDIR)
	mkdir -p $(INCDIR)
	mkdir -p $(LIBDIR)
	touch pre

$(DOWNLOADS)/binutils-$(BINUTILS_VERSION).tar.bz2:
	(cd $(DOWNLOADS); curl -O http://ftp.gnu.org/gnu/binutils/binutils-$(BINUTILS_VERSION).tar.bz2)

$(DOWNLOADS)/gcc-core-$(GCC_VERSION).tar.bz2:
	(cd $(DOWNLOADS); curl -O http://ftp.gnu.org/gnu/gcc/gcc-$(GCC_VERSION)/gcc-core-$(GCC_VERSION).tar.bz2)

binutils: $(DOWNLOADS)/binutils-$(BINUTILS_VERSION).tar.bz2
	tar xjf $(DOWNLOADS)/binutils-$(BINUTILS_VERSION).tar.bz2
	mkdir -p binutils-build
	(cd binutils-build; ../binutils-$(BINUTILS_VERSION)/configure --target=$(TARGET) --prefix=$(PREFIX) --disable-nls)
	(cd binutils-build; make all install)
	touch binutils

gcc: $(DOWNLOADS)/gcc-core-$(GCC_VERSION).tar.bz2
	tar xjf $(DOWNLOADS)/gcc-core-$(GCC_VERSION).tar.bz2
	mkdir -p gcc-build
	(cd gcc-build; ../gcc-$(GCC_VERSION)/configure --target=$(TARGET) --prefix=$(PREFIX) --with-incdir=$(INCDIR) --with-libdir=$(LIBDIR) --enable-languages=c --disable-nls --without-headers)
	(cd gcc-build; PATH=$(PATH):$(PREFIX)/$(TARGET)/bin make all-gcc && make install-gcc)
	touch gcc

clean:
	-rm pre binutils gcc
	-rm -rf binutils-build gcc-build
	-rm -rf binutils-$(BINUTILS_VERSION)
	-rm -rf gcc-core-$(GCC_VERSION)

.PHONY: all clean

