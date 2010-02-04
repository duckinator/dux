BINUTILS_VERSION=2.20
PCC_VERSION=091107
TARGET=i386-elf
PREFIX=$(HOME)/duxcc
DOWNLOADS=downloads
INCDIR=$(HOME)/duxincludes
LIBDIR=$(HOME)/duxlibs

all: pre binutils pcc

pre:
	mkdir -p $(DOWNLOADS)
	mkdir -p $(INCDIR)
	mkdir -p $(LIBDIR)
	mkdir -p $(PREFIX)
	touch pre

$(DOWNLOADS)/binutils-$(BINUTILS_VERSION).tar.bz2:
	(cd $(DOWNLOADS); curl -O http://ftp.gnu.org/gnu/binutils/binutils-$(BINUTILS_VERSION).tar.bz2)

$(DOWNLOADS)/pcc-$(PCC_VERSION).tgz:
	(cd $(DOWNLOADS); curl -O http://pcc.ludd.ltu.se/ftp/pub/pcc/pcc-$(PCC_VERSION).tgz)

binutils: $(DOWNLOADS)/binutils-$(BINUTILS_VERSION).tar.bz2
	tar xjf $(DOWNLOADS)/binutils-$(BINUTILS_VERSION).tar.bz2
	mkdir binutils-build
	(cd binutils-build; ../binutils-$(BINUTILS_VERSION)/configure --target=$(TARGET) --prefix=$(PREFIX) --disable-nls)
	(cd binutils-build; make all install)
	touch binutils

pcc: $(DOWNLOADS)/pcc-$(PCC_VERSION).tgz
	tar xzf $(DOWNLOADS)/pcc-$(PCC_VERSION).tgz
	mkdir pcc-build
	(cd pcc-build; ../pcc-091107/configure --target=$(TARGET) --prefix=$(PREFIX) --with-incdir=$(INCDIR) --with-libdir=$(LIBDIR))
	(cd pcc-build; make && make install)
	touch pcc

clean:
	-rm pre binutils pcc
	-rm -rf binutils-build pcc-build
	-rm -rf binutils-$(BINUTILS_VERSION)
	-rm -rf pcc-$(PCC_VERSION)

.PHONY: all clean

