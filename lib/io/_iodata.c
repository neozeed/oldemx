/* _iodata.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#define __IODATA

#include <sys/emx.h>
#include <fcntl.h>

int _files[_NFILES] = {O_TEXT, O_TEXT, O_TEXT};
