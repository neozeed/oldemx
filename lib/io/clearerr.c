/* clearerr.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdio.h>

void clearerr (FILE *stream)
    {
    stream->flags &= ~(_IOERR|_IOEOF);
    }
