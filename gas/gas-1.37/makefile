# Makefile -- changed for emx by Eberhard Mattes -- Feb 1992
#
# Makefile for GAS.
# Copyright (C) 1989, Free Software Foundation
# 
# This file is part of GAS, the GNU Assembler.
# 
# GAS is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 1, or (at your option)
# any later version.
# 
# GAS is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GAS; see the file COPYING.  If not, write to
# the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

# This makefile may be used to make the VAX, 68020, 80386, 
# SPARC, ns32k, or i860 assembler(s).

BINDIR = /emx/bin
CC = gcc

.c.o:
	$(CC) $(CFLAGS) -c $*.c

G0 = -g -I.
LDFLAGS = -L/emx/lib
# If you are on a BSD system, un-comment the next two lines, and comment out
# the lines for SystemV and HPUX below
#G0 = -g  -I. #-O -Wall
#LDFLAGS = $(CFLAGS)
#
# To compile gas on a System Five machine, comment out the two lines above
# and un-comment out the next three lines
# Comment out the -lPW on the LOADLIBES line if you are using GCC.
# G0 = -g -I. -DUSG
# LDFLAGS = $(CFLAGS)
# LOADLIBES = -lmalloc -lPW
#
# To compile gas for HPUX, link m-hpux.h to m68k.h , and un-comment the
# next two lines.  (If you are using GCC, comment out the alloca.o part)
# (Get alloca from the emacs distribution, or use GCC.)
# HPUX 7.0 may have a bug in setvbuf.  gas gives an error message like
# 1:"Unknown operator" -- Statement 'NO_APP' ignored
# if setvbuf is broken.  Re-compile input-file.c (and only input-file.c
# with -DVMS and the problem should go away.
#
# G0 = -g -I. -DUSG
# LOADLIBES = alloca.o
#
# To compile gas for a Sequent Symmetry, comment out all the above lines,
# and un-comment the next two lines.
# G0 = -g -I. -DUSE_SYSTEM_HDR -DEXEC_VERSION=1
# LOADLIBES = -lc /usr/att/lib/libc.a

# If you just want to compile the vax assembler, type 'make avax'

# If you just want to compile the i386 assembler, type 'make a386'

# If you just want to compile the ns32k assembler, type 'make a32k'

# If you just want to compile the sparc assembler, type 'make asparc'

# If you just want to compile the mc68020 assembler, make sure m68k.h
# is correctly set up, and type type 'make a68'  (Except on HPUX machines,
# where you will have to make the changes marked below before typing
# 'make a68'
# m68k.h should be a symbolic or hard-link to one of
# m-sun3.h , m-hpux.h or m-generic.h
# depending on which machine you want to compile the 68020 assembler for.
#
# If you want the 68k assembler to be completely compatable with the the
# SUN one, un-comment the -DSUN_ASM_SYNTAX line below.
#
# If you machine does not have vfprintf, but does have _doprnt(),
# remove the # from the -DNO_VARARGS line below.
#
# If the return-type of a signal-hander is void (instead of int),
# remove the # from the -DSIGTY line below.
#
# To include the mc68851 mmu coprocessor instructions in the 68020 assembler,
# remove the # from the -Dm68851 line below.
#
# If you want the 68020 assembler use a register prefix character, un-comment
# the REGISTER_PREFIX line, and (maybe) change the '%' to the appropriate
# character.
#
# If you want the assembler to treat .L* or ..* symbols as local, instead of
# the usual L* symbols, un-comment the DOT_LABEL_PREFIX line.
#
# If you want the 80386 assembler to correctly handle fsub/fsubr and fdiv/fdivr
# opcodes (unlike most 80386 assemblers), remove the # from
# the -DNON_BROKEN_WORDS line below.
#
# To compile 80386 Gas for the Sequent Symmetry, un-comment the -DEXEC_VERSION
# and the -DUSE_SYSTEM_HDR lines below.
#
# To compile gas for the HP 9000/300 un-comment the -DUSE_HP_HDR line below.
#
# For the ns32k, the options are 32532 or 32032 CPU and 32381 or 32081 FPU.
# To select the NS32532, remove the # from the -DNS32532 line below.
# To compile in tne NS32381 opcodes in addition to the NS32081 opcodes
# (the 32381 is a superset of the 32081), remove the # from the -DNS32381
# line below.
#
# For the ns32k on a Sequent, uncomment the SEQUENT_COMPATABILITY line below.
#
# If you want the .align N directive to align to the next N byte boundry,
# instead of the next 1<<N boundry, un-comment the OTHER_ALIGN line below.
# (This option is automatically enabled when building the sparc assembler.
#

O1 = # -DNO_VARARGS
O2 = # -DNON_BROKEN_WORDS
O3 = # -Dm68851
O4 = # -DEXEC_VERSION=1
O5 = # -DSIGTY=void
O6 = # -DNS32532
O6 = # -DNS32381
O7 = # -DDOT_LABEL_PREFIX
O8 = # -DSEQUENT_COMPATABILITY
O9 = # -DREGISTER_PREFIX=\'%\'
O10= # -DOTHER_ALIGN

G1 = # -DUSE_SYSTEM_HDR
G2 = # -DUSE_HP_HDR
G3 = # -DSUN_ASM_SYNTAX

OPTIONS = $(O1) $(O2) $(O3) $(O4) $(O5) $(O6) $(O7) $(O8) $(O9) $(O10)

CFLAGS = $(G0) $(G1) $(G2) $(G3) $(G4)

#
# To make the 68020 assembler compile as the default, un-comment the next
# line, and comment out all the other lines that start with DEFAULT_GAS
#DEFAULT_GAS=a68
#
# To make the VAX assembler compile as the default, un-comment the next
# line and commment out all the other lines that start with DEFAULT_GAS
#DEFAULT_GAS=avax
#
# To make the 80386 assembler compile as the default, un-comment the next
# line and commment out all the other lines that start with DEFAULT_GAS
DEFAULT_GAS=a386
#
# To make the ns32k assembler compile as the default, un-comment the next
# line and commment out all the other lines that start with DEFAULT_GAS
#DEFAULT_GAS=a32k
#
# To make the sparc assembler compile as the default, un-comment the next
# line and commment out all the other lines that start with DEFAULT_GAS
#DEFAULT_GAS=asparc
#
# To make the i860 assembler compile as the default, un-comment the next
# line and comment out all the other lines that start with DEFAULT_GAS
#DEFAULT_GAS=a860

# Global Sources -------------------------------------------------------------

a =\
as.o		xrealloc.o	xmalloc.o	hash.o		hex-valu.o   \
atof-gen.o	append.o	messages.o	expr.o		app.o         \
frags.o		input-fi.o	input-sc.o	output-f.o	              \
subsegs.o	symbols.o					version.o     \
fl-const.o  fl-copy.o   fl-mult.o   strstr.o        bignum-c.o \
obstack.o
#gdb.o		gdb-file.o	gdb-symbols.o	gdb-blocks.o	gdb-lines.o

gas:	$(DEFAULT_GAS)

# I860 GAS ------------------------------------------------------------------
u = i860.o  atof-ieee.o  write-i860.o  read-i860.o

U = i860.c  i860.h i860-opcode.h

i860.o:	i860.c i860.h i860-opcode.h as.h frags.h struc-symbol.h
i860.o:	flonum.h expr.h hash.h md.h write.h read.h symbols.h
	$(CC) -c $(CFLAGS) -DI860 i860.c

atof-ieee.o:	flonum.h

write-i860.o:	write.c i860.h
	$(CC) -c -DI860 $(CFLAGS) write.c
	mv write.o write-i860.o

read-i860.o: read.c i860.h
	$(CC) -c -DI860 $(CFLAGS) read.c
	mv read.o read-i860.o

a860: $a $u
	$(CC) -o a860 $(LDFLAGS) $a $u $(LOADLIBES)

# SPARC GAS ------------------------------------------------------------------
v = sparc.o  atof-ieee.o  write-sparc.o  read-sparc.o

V = sparc.c  sparc.h  sparc-opcode.h

atof-ieee.o:	flonum.h
sparc.o:	sparc.c sparc.h sparc-opcode.h as.h frags.h struc-symbol.h
sparc.o:	flonum.h expr.h hash.h md.h write.h read.h symbols.h
	$(CC) -c $(CFLAGS) -DSPARC sparc.c

write-sparc.o:	write.c
	$(CC) -c -DSPARC $(CFLAGS) write.c
	mv write.o write-sparc.o

read-sparc.o: read.c
	$(CC) -c -DSPARC $(CFLAGS) read.c
	mv read.o read-sparc.o

asparc: $a $v
	$(CC) -o asparc $(LDFLAGS) $a $v $(LOADLIBES)

# NS32K GAS ------------------------------------------------------------------
w = ns32k.o  atof-ieee.o  write-ns32k.o  read-ns32k.o

W = ns32k.c ns32k-opcode.h

atof-ieee.o:	flonum.h
ns32k.o:	as.h frags.h struc-symbol.h flonum.h expr.h md.h hash.h
ns32k.o:	write.h symbols.h ns32k-opcode.h ns32k.c
	$(CC) $(CFLAGS) $(OPTIONS) -c ns32k.c

write-ns32k.o:	write.c
	$(CC) -c -DNS32K $(CFLAGS) write.c
	mv write.o write-ns32k.o

read-ns32k.o:
	$(CC) -c -DNS32K $(CFLAGS) read.c
	mv read.o read-ns32k.o

a32k: $a $w
	$(CC) -o a32k $(LDFLAGS) $a $w $(LOADLIBES)

# 80386 GAS ------------------------------------------------------------------
x = i386.o  atof-iee.o  write.o  read.o

X = i386.c  i386.h  i386-opc.h

i386.o:		i386.c as.h read.h flonum.h frags.h struc-symbol.h expr.h
i386.o:		symbols.h hash.h md.h i386.h i386-opc.h
	$(CC) $(CFLAGS) $(OPTIONS) -c i386.c

atof-iee.o:	flonum.h

a386: $a $x a386.ld
	$(CC) -o a386 $(LDFLAGS) @a386.ld $(LOADLIBES)

# 68020 GAS ------------------------------------------------------------------
y = m68k.o  atof-ieee.o write.o read.o

Y = m68k.c atof-ieee.c m68k-opcode.h m-hpux.h m-sun3.h m-generic.h

atof-ieee.o:	flonum.h

m68k.o:		m68k.c a_out_gnu.h as.h expr.h flonum.h frags.h hash.h
m68k.o:		m68k-opcode.h m68k.h md.h obstack.h struc-symbol.h
	$(CC) $(CFLAGS) $(OPTIONS) -c m68k.c

a68: $a $y
	$(CC) -o a68 $(LDFLAGS) $a $y $(LOADLIBES)

# VAX GAS --------------------------------------------------------------------
z = vax.o  atof-vax.o  write.o  read.o

Z = vax.c atof-vax.c vax-opcode.h vax-inst.h \
    make-gas.com objrecdef.h vms.c vms-dbg.c README-vms-dbg

vax.o:		vax.c a_out_gnu.h as.h expr.h flonum.h frags.h md.h obstack.h
vax.o:		read.h struc-symbol.h symbols.h vax-inst.h vax-opcode.h
atof-vax.o:	as.h flonum.h read.h

avax:	$a $z
	$(CC) -o avax $(LDFLAGS) $a $z $(LOADLIBES)

# global files ---------------------------------------------------------------

as.o: as.c
	$(CC) $(CFLAGS) $(OPTIONS) -c as.c

messages.o: messages.c
	$(CC) $(CFLAGS) $(OPTIONS) -c messages.c

hash.o:	hash.c
	$(CC) $(CFLAGS) -Derror=as_fatal -c hash.c

xmalloc.o:	xmalloc.c
	$(CC) $(CFLAGS) -Derror=as_fatal -c xmalloc.c

xrealloc.o:	xrealloc.c
	$(CC) $(CFLAGS) -Derror=as_fatal -c xrealloc.c

A =\
as.c		xrealloc.c	xmalloc.c	hash.c		hex-valu.c \
atof-gen.c	append.c	messages.c	expr.c		bignum-c.c \
frags.c		input-fi.c	input-scr.c	output-f.c	read.c \
subsegs.c	symbols.c	write.c				strstr.c \
fl-const.c  fl-copy.c   fl-mult.c   app.c           version.c \
obstack.c \
#gdb.c		gdb-file.c	gdb-symbols.c	gdb-blocks.c \
#gdb-lines.c

H = \
as.h		bignum.h	expr.h		flonum.h \
frags.h		hash.h		input-fi.h	md.h	 \
obstack.h	read.h		struc-symbol.h	subsegs.h	\
symbols.h	write.h

dist: COPYING README ChangeLog $A $H $Z $Y $X $W $V $U Makefile
	echo gas-`sed -n -e '/ version /s/[^0-9.]*\([0-9.]*\).*/\1/p' < version.c` > .fname
	mkdir `cat .fname`

	ln COPYING README ChangeLog $A $H $Z $Y $X $W $V $U Makefile `cat .fname`
	tar cvhZf `cat .fname`.tar.Z `cat .fname`
	-rm -r `cat .fname`
	-rm .fname

clean:
	-del *.o
	-del a386

install:	a
	cp a $(BINDIR)/gas


# General .o-->.h dependencies

app.o:		as.h
as.o:           as.h read.h struc-symbol.h write.h
atof-gen.o:	flonum.h
bignum-c.o:	bignum.h
expr.o:         as.h expr.h flonum.h obstack.h read.h struc-symbol.h
expr.o:		 symbols.h
fl-const.o: flonum.h
fl-copy.o:  flonum.h
fl-mult.o:  flonum.h
fl-normal.o:flonum.h
fl-print.o: flonum.h
frags.o:        as.h frags.h obstack.h struc-symbol.h subsegs.h
#gdb.o:		as.h
#gdb-blocks.o:	as.h
#gdb-lines.o:	as.h frags.h obstack.h
#gdb-symbols.o:	a_out_gnu.h as.h struc-symbol.h
hash.o:		hash.h
input-fi.o:	input-fi.h
input-sc.o:	as.h input-fi.h read.h
messages.o:	as.h
obstack.o:	obstack.h
read.o:         as.h expr.h flonum.h frags.h hash.h md.h obstack.h
read.o:		read.h struc-symbol.h symbols.h
subsegs.o:      as.h frags.h obstack.h struc-symbol.h subsegs.h write.h
symbols.o:      as.h frags.h hash.h obstack.h struc-symbol.h symbols.h
write.o:        as.h md.h obstack.h struc-symbol.h subsegs.h
write.o:	symbols.h write.h

flonum.h:					bignum.h
