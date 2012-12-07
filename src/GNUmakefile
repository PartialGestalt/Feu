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
firstrule: all

HDRS= \
	feu.h

LIB=FEU.xbs

LIB_SRCS= \
	feu_object.c

LIB_TEMPS=$(LIB_SRCS:.c=.i) $(LIB_SRCS:.c=.s)

LIB_OBJS=$(LIB_SRCS:.c=.o)

TEST=feu_test

TEST_SRCS= \
	feu_test.c

TEST_TEMPS=$(TEST_SRCS:.c=.i) $(TEST_SRCS:.c=.s)

TEST_OBJS=$(TEST_SRCS:.c=.o)

PACKAGE=screensaver.pg.feu
VERSION=0.8.1
PKGROOT=pkg

CINCFLAGS+=
CDEBUGFLAGS+=-save-temps

CFLAGS+=-fPIC $(CINCFLAGS) $(CDEBUGFLAGS)

LD_LIBS+=

LDFLAGS+=$(LD_LIBS)

CLEANFILES=$(LIB) $(LIB_OBJS) $(TEST_OBJS) $(PKGROOT) $(LIB_TEMPS) $(TEST_TEMPS)
CLOBBERFILES=$(CLEANFILES) cscope.out cscope.files

.PHONY: all clean clobber fresh install pkg cscope

all: $(LIB) 

test: $(TEST)

clean::
	-rm -rf $(CLEANFILES)

clobber::
	-rm -rf $(CLOBBERFILES)


fresh: clean all


$(LIB): $(LIB_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -o $@ $(LIB_OBJS)


cscope: cscope.out
   
cscope.out: cscope.files
	cscope -bi cscope.files

cscope.files::
	find . -type f -name '*.[ch]' -print | tee $@


$(TEST): $(LIB) $(TEST_OBJS) 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(TEST_OBJS) $(LIB)
