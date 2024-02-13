/* eof.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <io.h>

int eof (int handle)
    {
    long cur, len;

    cur = tell (handle);
    if (cur < 0)
        return (-1);
    len = filelength (handle);
    if (len < 0)
        return (-1);
    return (cur == len);
    }
