BUILD_ROOT=..
include $(BUILD_ROOT)/common.mk


LIB=../src/FeuSS.xbs

ADDONXML=addon.xml
ADDONXML_SRCS=$(ADDONXML).in

PACKAGE=screensaver.pg.feu
VERSION=0.9.0

PKGROOT=pkg
PKGDIR=$(PKGROOT)/$(PACKAGE)
FULLPKGDIR=$(realpath $(PKGROOT))
FULLPKGNAME=$(PACKAGE).$(VERSION).zip
FULLPKG=$(FULLPKGDIR)/$(FULLPKGNAME)

PKGDEPS=$(LIB) $(ADDONXML) icon.png resources/settings.xml resources/language/English/strings.xml
PKGBITS=$(LIB) $(ADDONXML) icon.png resources


CLEANFILES=$(PKGROOT) $(ADDONXML)
CLOBBERFILES=$(PKGROOT) $(ADDONXML)


.PHONY: all clean clobber fresh install pkg cscope

install: pkg
	$(SAY_IT) "[ INSTALL ]" $(PACKAGE).$(VERSION).zip ' --> ' XBMC
	$(DO_IT)-(cd ~/.xbmc/addons && unzip -q -o $(FULLPKG))
#	cp $(LIB) ~/.xbmc/addons/screensaver.pg.xs-bridge

pkg-checkdir:
	@-if [ ! -d $(PKGDIR) ] ; then mkdir -p $(PKGDIR) ; fi

pkg-prep: $(PKGDEPS) pkg-checkdir
	$(SAY_IT) "[ PKGPREP ]" $(PACKAGE).$(VERSION)
	$(DO_IT)cp -aux $(PKGBITS) $(PKGDIR)/

pkg: pkg-prep
	$(SAY_IT) "[   ZIP   ]" $(FULLPKGNAME)
	$(DO_IT)(cd pkg && zip -r -l -q $(FULLPKGNAME) $(PACKAGE))

$(ADDONXML): $(ADDONXML_SRCS) GNUmakefile
	$(SAY_IT) "[ XMLPREP ]" $@
	$(DO_IT) -cat $(ADDONXML_SRCS) | sed -e 's/_PACKAGE_/$(PACKAGE)/g' -e 's/_VERSION_/$(VERSION)/g' > $@
        

fresh: clean all

all::
	$(NOTHING)	

