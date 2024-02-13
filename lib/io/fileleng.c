/* fileleng.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <io.h>

long filelength (int handle)
    {
    long cur, n;

    cur = lseek (handle, 0L, SEEK_CUR);
    if (cur < 0)
        return (cur);
    n = lseek (handle, 0L, SEEK_END);
    (void)lseek (handle, cur, SEEK_SET);
    return (n);
    }
