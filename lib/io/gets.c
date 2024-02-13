/* gets.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdio.h>

char *gets (char *buffer)
    {
    int c;
    char *dst;

    dst = buffer;
    for (;;)
        {
        c = getchar ();
        if (c == EOF)
            if (dst == buffer)
                {
                *dst = 0;
                return (NULL);
                }
            else
                break;
        if (c == '\n')
            break;
        *dst++ = (char)c;
        }
    *dst = 0;
    return (buffer);
    }
