/* fcloseal.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>

int fcloseall (void)
    {
    int i, n;
    char ok;

    n = 0; ok = 1;
    for (i = 3; i < _nfile; ++i)              /* keep stdin, stdout, stderr */
        if (_streams[i].flags & F_INUSE)
            if (fclose (&_streams[i]) == 0)
                ++n;
            else
                ok = 0;
    return (ok ? n : EOF);
    }
