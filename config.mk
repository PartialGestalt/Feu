#######################################################################
##
## @file Makefile support definitions for FEU 
##
## @details
## This file may be included from any makefile in the tree, in order
## to get some basic support definitions.
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


# BUILD_CONFIG must be one of "DEBUG" or "RELEASE".  This is 
# "DEBUG" by default, but may be changed explicitly with an
# environment variable or by building the 'release' target.

ifeq ($(BUILD_CONFIG),)
BUILD_CONFIG="DEBUG"
endif


# Options for debug builds
CPPDEBUGFLAGS=-save-temps -DFEU_DEBUG -O0
CDEBUGFLAGS=$(CPPDEBUGFLAGS)

# Options for release builds
CPPRELEASEFLAGS=-O3
CRELEASEFLAGS=$(CPPRELEASEFLAGS)

# Options for target machine
CPPMACHFLAGS=-fPIC
CMACHFLAGS=$(CPPMACHFLAGS)

# Combine as appropriate
CPPFLAGS+=$(CPPMACHFLAGS) $(CPP$(BUILD_CONFIG)FLAGS)


# Common libs (don't use much here, most libs should
# be in local particular makefiles.
LDCOMMONLIBS=-lstd++
