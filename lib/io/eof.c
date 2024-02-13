/* eof.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <io.h>

int eof (int handle)
    {
    long cur;

    cur = fseek (handle, 0L, SEEK_CUR);
    if (cur < 0) return (-1L);
    return (cur == filelength (handle) ? 1 : 0);
    }
