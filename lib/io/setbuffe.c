/* setbuffe.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdio.h>

int setbuffer (FILE *stream, char *buffer, size_t size)
    {
    return (setvbuf (stream, buffer, _IOFBF, size));
    }
