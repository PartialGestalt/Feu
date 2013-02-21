#######################################################################
##
## @file GNUmakefile for FEU source
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

BUILD_ROOT=..

include $(BUILD_ROOT)/common.mk

firstrule: all

CLASS_SRCS=$(wildcard Feu[A-Z]*.cpp) Feu.cpp

CLASS_HDRS=$(CLASS_SRCS:.cpp=.h)

HDRS= \
	feu.h \
	$(CLASS_HDRS)

LIB=libFEU.so

LIB_SRCS=$(CLASS_SRCS)

LIB_TEMPS=$(LIB_SRCS:.cpp=.ii) $(LIB_SRCS:.cpp=.s)

LIB_OBJS=$(LIB_SRCS:.cpp=.o)

LIB_LDFLAGS=-ltinyxml

XBMC_SS_LIB=FeuSS.xbs

XBMC_SS_SRCS=FeuXBMCScreenSaver.cpp

XBMC_SS_TEMPS=$(XBMC_SS_SRCS:.cpp=.ii) $(XBMC_SS_SRCS:.cpp=.s)

XBMC_SS_OBJS=$(XBMC_SS_SRCS:.cpp=.o)

XBMC_SS_LDFLAGS=-L . -lFEU

TEST=feutest

TEST_SRCS= \
	feutest.cpp

TEST_OBJS=$(TEST_SRCS:.cpp=.o)

TEST_TEMPS=$(TEST_SRCS:.cpp=.ii) $(TEST_SRCS:.cpp=.s)

CALC=feucalc
CALC_SRCS=feucalc.cpp
CALC_OBJS=$(CALC_SRCS:.cpp=.o)
CALC_TEMPS=$(CALC_SRCS:.cpp=.ii) $(CALC_SRCS:.cpp=.s)

PACKAGE=screensaver.pg.feu
VERSION=0.8.1
PKGROOT=pkg

CLEANFILES=$(LIB) $(XBMC_SS_LIB) $(LIB_OBJS) $(XBMC_SS_OBJS) $(TEST) $(TEST_OBJS) $(CALC) $(CALC_OBJS) $(PKGROOT) $(LIB_TEMPS) $(TEST_TEMPS) $(CALC_TEMPS) $(XBMC_SS_TEMPS)
CLOBBERFILES=$(CLEANFILES) cscope.out cscope.files

.PHONY: all clean clobber fresh install pkg cscope

all: $(LIB) $(XBMC_SS_LIB) $(TEST) $(CALC)

test: $(TEST)
	$(VALGRINDER) ./$(TEST)

$(LIB): $(LIB_OBJS)
	$(SHAREDLIB) $(LIB_LDFLAGS)

$(XBMC_SS_LIB): $(LIB) $(XBMC_SS_OBJS)
	$(SHAREDLIB) $(XBMC_SS_LDFLAGS)

$(TEST): $(TEST_OBJS) $(LIB)
	$(LINKPROG)

$(CALC): $(CALC_OBJS) $(LIB)
	$(LINKPROG)
