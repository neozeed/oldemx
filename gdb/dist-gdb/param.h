/* param.h -- changed for emx by Eberhard Mattes -- Jan 1992 */

/* Macro definitions for i386 using the GNU object file format.
   Copyright (C) 1986, 1987, 1989 Free Software Foundation, Inc.

This file is part of GDB.

GDB is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 1, or (at your option)
any later version.

GDB is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GDB; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

/*
 * Changes for 80386 by Pace Willisson (pace@prep.ai.mit.edu)
 * July 1988
 */


#include "m-i386.h"


#define NAMES_HAVE_UNDERSCORE

#undef COFF_FORMAT
#define READ_DBX_FORMAT
#undef HAVE_TERMIO
#undef START_INFERIOR_TRAPS_EXPECTED
#define START_INFERIOR_TRAPS_EXPECTED 1
#define CANNOT_EXECUTE_STACK

int _seek_hdr (int fd);

#define HEADER_SEEK_FD(X) { (void)_seek_hdr (X); hdr_off = tell (X);}
#define STRING_TABLE_OFFSET (N_SYMOFF (hdr) + hdr.a_syms + hdr_off)
#define DECLARE_FILE_HEADERS  AOUTHDR hdr; long hdr_off
#define SYMBOL_TABLE_OFFSET (N_SYMOFF (hdr) + hdr_off)

#undef FIX_CALL_DUMMY
#define FIX_CALL_DUMMY(dummyname, pc, fun, nargs, type)   \
{ \
    int from, to, delta, loc; \
    extern CORE_ADDR text_end; \
    loc = (int)(text_end - CALL_DUMMY_LENGTH); \
    from = loc + 5; \
    to = (int)(fun); \
    delta = to - from; \
    *(int *)((char *)(dummyname) + 1) = delta; \
}

#define PATHSEP(c) ((c) == '/' || (c) == '\\')
#define ABSPATH(s) (PATHSEP (s[0]) || (s[0] != 0 && s[1] == ':'))
