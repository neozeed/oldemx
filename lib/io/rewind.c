/* rewind.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdio.h>

void rewind (FILE *stream)
    {
    (void)fseek (stream, 0L, SEEK_SET);
    stream->flags &= ~_IOERR;
    }
