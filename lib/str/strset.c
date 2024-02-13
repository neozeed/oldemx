/* strset.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <string.h>

char *strset (char *string, int c)
    {
    char *dst;

    dst = string;
    while (*dst != 0)
        *dst++ = (char)c;
    return (string);
    }
