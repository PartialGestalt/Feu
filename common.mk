#######################################################################
##
## @file Makefile support rules for FEU 
##
## @details
## This file may be included from any makefile in the tree, in order
## to get some basic support rules.
## <em>Copyright (C) 2012, Andrew Kephart (akephart@akephart.org)</em>.
##
## Permission to use, copy, modify, distribute, and sell this software and its
## documentation for any purpose is hereby granted without fee, provided that
## the above copyright notice appear in all copies and that both that
## copyright notice and this permission notice appear in supporting
## documentation.  No representations are made about the suitability of this
## software for any purpose.  It is provided "as is" without express or 
## implied warranty.
##
#######################################################################
## Some versions of make use the first-defined rule as the default.
firstrule: all

##
## Usage: Before the 'include' line in the calling makefile, you
##        should define a few variables:
##        "BUILD_ROOT" (required, relative path to top of tree)
##        "SUBDIRS"    (required for descending into subdirs, list of subdirs)
##        "V"          (if set to "1", turns on verbose mode)
##

BUILD_CURDIR=$(shell pwd)
BUILD_TOPDIR=$(shell cd $(BUILD_ROOT); pwd)
BUILD_SUBDIR=$(subst $(BUILD_TOPDIR)/,,$(BUILD_CURDIR))

include $(BUILD_ROOT)/config.mk

ifneq ($(SUBDIRS),)
DESCEND=@(if [ "$(SUBDIRS)" != "" ] ; then for subdir in $(SUBDIRS); do $(MAKE) -C $$subdir $@ || exit 1; done; fi)
else
DESCEND=@echo "[ RETURN  ]"
endif

ifeq ($(V),1)
SAY_IT=@true
DO_IT=
else
SAY_IT=@echo
DO_IT=@
endif

NOTHING=@/bin/true


##
## Make implicit rules explicit
##
%.o:%.cpp
	$(SAY_IT) "[ COMPILE ]" $@
	$(DO_IT) $(CCC) $(CPPFLAGS) -c -o $@ $<


##
## Common rules
##
fresh: clean all

clean::
	$(SAY_IT) "[  CLEAN  ]" 
	$(DO_IT) -rm -rf $(CLEANFILES)

clobber::
	$(SAY_IT) "[ CLOBBER ]"
	$(DO_IT) -rm -rf $(CLOBBERFILES)

release::
	$(NOTHING)


define SHAREDLIB
	$(SAY_IT) "[SHAREDLIB]" $@
	$(DO_IT) $(CCC) -shared -o $@ $^ $(LDFLAGS)
endef

define LINKPROG
	$(SAY_IT) "[  LINK   ]" $@
	$(DO_IT) $(CCC) -o $@ $^ $(LDFLAGS)
endef


##
## Cscope
##
cscope: cscope.out
   
cscope.out: cscope.files
	cscope -bi cscope.files

cscope.files::
	find . -type f -name '*.[ch]' -print | tee $@

