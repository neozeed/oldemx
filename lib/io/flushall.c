/* flushall.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>

int flushall (void)
    {
    int i, n;

    n = 0;
    for (i = 0; i < _nfile; ++i)
        if (_streams[i].flags & F_INUSE)
            if (fflush (&_streams[i]) == 0)
                ++n;
    return (n);
    }
