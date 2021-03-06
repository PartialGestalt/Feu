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
ifneq ($(findstring release,$(MAKECMDGOALS)),)
BUILD_CONFIG=RELEASE
VALGRINDER:=
endif

ifeq ($(BUILD_CONFIG),)
BUILD_CONFIG=DEBUG

VALGRIND=valgrind
ifeq (TRUE,$(if $(shell which $(VALGRIND) 2>/dev/null),TRUE,FALSE))
VALGRINDER:=$(VALGRIND) --leak-check=full
else
VALGRINDER:=
endif
endif

.PHONY: release

# Options for debug builds
CPPDEBUGFLAGS=-g -DFEU_DEBUG -O0 #-save-temps
CDEBUGFLAGS=$(CPPDEBUGFLAGS)

# Options for release builds
CPPRELEASEFLAGS=-O3
CRELEASEFLAGS=$(CPPRELEASEFLAGS)

# Options for target machine
CPPMACHFLAGS=-fPIC
CMACHFLAGS=$(CPPMACHFLAGS)

# Extra includes
CPPINCFLAGS+=-I$(BUILD_ROOT)/xbmc

# Combine as appropriate
CPPFLAGS+=$(CPPMACHFLAGS) $(CPP$(BUILD_CONFIG)FLAGS) $(CPPINCFLAGS)

# Common libs (don't use much here, most libs should
# be in local particular makefiles.
LDCOMMONLIBS=-lstdc++

# Add the current dir to runtime path search
LDCOMMONFLAGS=-Wl,-rpath=./

LDFLAGS+=$(LDCOMMONFLAGS) $(LDCOMMONLIBS)

#
# Make sure we're gcc everywhere....
CC=gcc
CCC=g++


#
# Debug tools
#
