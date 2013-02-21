#######################################################################
##
## @file GNUmakefile for FEU toplevel
##
## @details
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
BUILD_ROOT=.

firstrule: all
SUBDIRS=src ss #vis

include $(BUILD_ROOT)/common.mk

clean:: 
	$(DESCEND)

clobber:: 
	$(DESCEND)


.DEFAULT:
	$(DESCEND)
