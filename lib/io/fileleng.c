/* fileleng.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>

long filelength (int handle)
    {
    long cur, n;

    cur = (long)__lseek (handle, 0L, SEEK_CUR);
    if (cur == -1L)
        return (-1L);
    n = (long)__lseek (handle, 0L, SEEK_END);
    (void)__lseek (handle, cur, SEEK_SET);
    return (n);
    }
