/* fgetc.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdio.h>

int fgetc (FILE *stream)
    {
    return (getc (stream));
    }
