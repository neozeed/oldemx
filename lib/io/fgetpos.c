/* fgetpos.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdio.h>

int fgetpos (FILE *stream, fpos_t *pos)
    {
    if ((*pos = ftell (stream)) == (long)EOF)
        return (EOF);
    else
        return (0);
    }
