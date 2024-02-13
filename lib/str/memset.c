/* memset.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <string.h>

void *memset (void *s, int c, int n)
    {
    int i;

    for (i = 0; i < n; ++i)
        ((char *)s)[i] = (char)c;
    return (s);
    }
