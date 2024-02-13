/* fputs.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdio.h>
#include <string.h>

int fputs (const char *string, FILE *stream)
    {
    int result, len;

    _tmpbuf (stream);
    len = strlen (string);
    if (len == 0 || fwrite (string, len, 1, stream) == 1)
        result = 0;
    else
        result = EOF;
    _endbuf (stream);
    return (result);
    }
