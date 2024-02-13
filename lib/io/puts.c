/* puts.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdio.h>
#include <string.h>

int puts (const char *string)
    {
    int result, len;

    _tmpbuf (stdout);
    len = strlen (string);
    if (len == 0 || fwrite (string, len, 1, stdout) == 1)
        result = putchar ('\n');
    else
        result = EOF;
    _endbuf (stdout);
    return (result);
    }
