/* config.h -- changed for emx by Eberhard Mattes -- Mar 1992 */

/* Configuration for GNU C-compiler for Intel 80386.
   Copyright (C) 1988 Free Software Foundation, Inc.

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

#ifndef i386
#define i386
#endif

/* #defines that need visibility everywhere.  */
#define FALSE 0
#define TRUE 1

/* This describes the machine the compiler is hosted on.  */
#define HOST_BITS_PER_CHAR 8
#define HOST_BITS_PER_SHORT 16
#define HOST_BITS_PER_INT 32
#define HOST_BITS_PER_LONG 32
#define HOST_BITS_PER_LONGLONG 64

/* Arguments to use with `exit'.  */
#define SUCCESS_EXIT_CODE 0
#define FATAL_EXIT_CODE 33

/* If compiled with GNU C, use the built-in alloca */
#ifdef __GNUC__
#define alloca __builtin_alloca
#endif

/* target machine dependencies.
   tm.h is a symbolic link to the actual target specific file.   */

#include "tm.h"

#ifndef __EMX__
#define __EMX__
#endif
#define USG
#define GCC_INCLUDE_DIR            "/emx/include"
#define GPLUSPLUS_INCLUDE_DIR      "/emx/include/gpp"
#define STANDARD_EXEC_PREFIX       "/emx/bin/"
#define STANDARD_STARTFILE_PREFIX  "/emx/lib/"
#define DEFAULT_TARGET_MACHINE     "emx"
#define EXECUTABLE_SUFFIX          ".exe"
#define CPP_SPEC                   "-D__EMX__"

#undef TARGET_SWITCHES
#define TARGET_SWITCHES  \
  { { "80387", 1},				\
    { "soft-float", -1},			\
    { "486", 2},				\
    { "no486", -2},				\
    { "386", -2},				\
    { "rtd", 8},				\
    { "nortd", -8},				\
    { "regparm", 020},				\
    { "noregparm", -020},                       \
    { "probe", 040},				\
    { "noprobe", -040}, 			\
    { "", TARGET_DEFAULT}}

/* Use a stack probe */
#define TARGET_PROBE (target_flags & 040)

#undef TARGET_DEFAULT
#define TARGET_DEFAULT 041      /* 80387 and stack probe */

#define PROBE_SIZE         0x1000
#define PROBE_MAX_INLINE   0x10000

/* #pragma (pack): copied from config/i386v4.h */

/* Biggest alignment that any structure field can require on this
   machine, in bits.  If packing is in effect, this can be smaller than
   normal.  */

#define BIGGEST_FIELD_ALIGNMENT \
  (maximum_field_alignment ? maximum_field_alignment : 32)

extern int maximum_field_alignment;

/* If bit field type is int, don't let it cross an int,
   and give entire struct the alignment of an int.  */
/* Required on the 386 since it doesn't have bitfield insns.  */
/* If packing is in effect, then the type doesn't matter.  */

#undef PCC_BITFIELD_TYPE_MATTERS
#define PCC_BITFIELD_TYPE_MATTERS (maximum_field_alignment == 0)

/* Code to handle #pragma directives.  The interface is a bit messy,
   but there's no simpler way to do this while still using yylex.  */
#define HANDLE_PRAGMA(FILE)					\
  do {								\
    while (c == ' ' || c == '\t')				\
      c = getc (FILE);						\
    if (c == '\n' || c == EOF)					\
      {								\
	handle_pragma_token (0, 0);				\
	return c;						\
      }								\
    ungetc (c, FILE);						\
    switch (yylex ())						\
      {								\
      case IDENTIFIER:						\
      case TYPENAME:						\
      case STRING:						\
      case CONSTANT:						\
	handle_pragma_token (token_buffer, yylval.ttype);	\
	break;							\
      default:							\
	handle_pragma_token (token_buffer, 0);			\
      }								\
    if (nextchar >= 0)						\
      c = nextchar, nextchar = -1;				\
    else							\
      c = getc (FILE);						\
  } while (1)
