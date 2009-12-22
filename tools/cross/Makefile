BINUTILS_VERSION=2.20
PCC_VERSION=091107
TARGET=i386-dux
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
	(cd $(DOWNLOADS); wget http://ftp.gnu.org/gnu/binutils/binutils-$(BINUTILS_VERSION).tar.bz2)

$(DOWNLOADS)/pcc-$(PCC_VERSION).tgz:
	(cd $(DOWNLOADS); wget http://pcc.ludd.ltu.se/ftp/pub/pcc/pcc-$(PCC_VERSION).tgz)

$(DOWNLOADS)/binutils-dux.patch:
	(cd $(DOWNLOADS); wget http://gist.github.com/raw/229374/a3cf5f477f4c62cd4b7234d6ee51c3f77694cd7b/binutils-dux.patch)

$(DOWNLOADS)/pcc-dux.patch:
	(cd $(DOWNLOADS); wget http://gist.github.com/raw/228548/7c846de52862fe5e360278619d69a17ad164370a/pcc-dux.patch)

binutils: $(DOWNLOADS)/binutils-$(BINUTILS_VERSION).tar.bz2 $(DOWNLOADS)/binutils-dux.patch
	tar xjf $(DOWNLOADS)/binutils-$(BINUTILS_VERSION).tar.bz2
	(cd binutils-$(BINUTILS_VERSION); patch -p1 < ../$(DOWNLOADS)/binutils-dux.patch)
	mkdir binutils-build
	(cd binutils-build; ../binutils-$(BINUTILS_VERSION)/configure --target=$(TARGET) --prefix=$(PREFIX) --disable-nls)
	(cd binutils-build; make all install)
	touch binutils

pcc: $(DOWNLOADS)/pcc-$(PCC_VERSION).tgz $(DOWNLOADS)/pcc-dux.patch
	tar xzf $(DOWNLOADS)/pcc-$(PCC_VERSION).tgz
	(cd pcc-$(PCC_VERSION); patch -p1 < ../$(DOWNLOADS)/pcc-dux.patch)
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

