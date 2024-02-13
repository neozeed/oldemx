/* fsetpos.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdio.h>

int fsetpos (FILE *stream, const fpos_t *pos)
    {
    return (fseek (stream, *pos, SEEK_SET));
    }
