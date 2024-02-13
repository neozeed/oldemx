/* fgets.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdio.h>

char *fgets (char *buffer, int n, FILE *stream)
    {
    int c;
    char *dst;

    if (n <= 0)
        return (NULL);
    dst = buffer;
    while (n > 1)
        {
        c = getc (stream);
        if (c == EOF)
            if (dst == buffer)
                {
                *dst = 0;
                return (NULL);
                }
            else
                break;
        *dst++ = (char)c;
        if (c == '\n')
            break;
        --n;
        }
    *dst = 0;
    return (buffer);
    }
