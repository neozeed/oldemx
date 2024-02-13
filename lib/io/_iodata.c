/* _iodata.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#define __IODATA

#include <sys/emx.h>
#include <fcntl.h>

const int _nfiles = _NFILES;
int _files[_NFILES] = {O_TEXT, O_TEXT, O_TEXT};
int _lookahead[_NFILES] = {-1, -1, -1};
