/* fputc.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdio.h>

int fputc (int c, FILE *stream)
    {
    return (putc (c, stream));
    }
