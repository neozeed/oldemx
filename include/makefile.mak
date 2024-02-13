#
# /emx/include/makefile.mak
#
.SUFFIXES: .o
EMXBIN=\emx\bin\#
CC=$(EMXBIN)gcc
LD=$(EMXBIN)ld
AR=$(EMXBIN)ar
NM=$(EMXBIN)nm
AS=$(EMXBIN)as
CPP=$(EMXBIN)cpp
CFLAGS=
.c.o:
        $(CC) -c $(CFLAGS) $<
