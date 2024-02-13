/* freopen.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>

FILE *freopen (const char *fname, const char *mode, FILE *stream)
    {
    if (stream->flags & F_INUSE)
        if (fclose (stream) != 0)
            return (NULL);
    return (_fopen (stream, fname, mode));
    }
