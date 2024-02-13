# Generated automatically from Makefile.in by configure.
# Makefile for the info sources... -*- text -*-
# Copyright (C) 1990, 1991 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

SHELL = /bin/sh

#### Start of system configuration section. ####

srcdir = .

CC = gcc -O
INSTALL = /usr/bin/install -c
INSTALLDATA = /usr/bin/install -c -m 644

# Things you might add to DEFS:
# -DSTDC_HEADERS	If you have ANSI C headers and libraries.
# -DHAVE_UNISTD_H	If you have unistd.h.
# -DUSG			If you have System V/ANSI C string and
#			memory functions and headers.
# -DUSGr3		If you need to include sys/stream.h and sys/ptem.h
#			to get the screen size from the kernel.
DEFS =  -DSTDC_HEADERS -DUSG

# As with any program that uses the system ioctl () command, if you are
# compiling that program with Gcc, and you do not have fixed include
# files installed, then you should use the -traditonal flag to process
# the file.  Of course, this is only if your gcc calls GNU cpp.
#
# What this means is -- if Info doesn't seem to work, and you have
# compiled it with Gcc, add -traditional to CFLAGS and try again.
#	GCC_TRADITIONAL = -traditional
CDEBUG = -g
CFLAGS = $(CDEBUG) $(DEFS) $(GCC_TRADITIONAL)
LDFLAGS = -g

LIBS = 

prefix = /emx

# Where installed binaries go.
bindir = $(prefix)/new

# Where info files go.
infodir = $(prefix)/info

#### End of system configuration section. ####

SOURCES = info.c makeinfo.c getopt.c getopt1.c
OBJECTS = info.o makeinfo.o getopt.o getopt1.o
HEADERS = getopt.h
SUPPORT = Makefile.in configure 

THINGS_TO_TAR = $(SOURCES) $(HEADERS) $(SUPPORT)

PROGS = info.exe makeinfo.exe

all: $(PROGS)

info.exe: info
	strip info
	emxbind -b /emx/bin/emxl.exe info info.exe

makeinfo.exe : makeinfo
	strip makeinfo
	emxbind -b /emx/bin/emxl.exe makeinfo makeinfo.exe

info:	info.o getopt.o getopt1.o
	$(CC) $(LDFLAGS) -o $@ info.o getopt.o getopt1.o -ltermcap $(LIBS)

info.o: info.c
	$(CC) -c $(CFLAGS) info.c

makeinfo: makeinfo.o getopt.o getopt1.o
	$(CC) $(LDFLAGS) -o $@ makeinfo.o getopt.o getopt1.o $(LIBS)

makeinfo.o: makeinfo.c
	$(CC) -c $(CFLAGS) makeinfo.c

info.o makeinfo.o getopt1.o: getopt.h

install: info.exe makefile.exe dir info.inf
	copy makefile.exe $(bindir)/makefile.exe
	copy info.exe $(bindir)/info.exe
	copy dir $(infodir)/dir
	copy info.inf $(infodir)/info.inf

TAGS: $(SOURCES)
	etags $(SOURCES)

clean:
	rm -f $(PROGS) $(OBJECTS)

distclean: clean
	-rm -f TAG

realclean: distclean

dist: $(THINGS_TO_TAR)
	rm -rf info-dist
	mkdir info-dist
	(cd info-dist; for i in $(THINGS_TO_TAR); do ln -s ../$$i .; done)
	tar chzf info.tar.Z info-dist
	rm -rf info-dist
