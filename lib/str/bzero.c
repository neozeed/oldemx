/* bzero.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <strings.h>

void bzero (void *s, int n)
    {
    int i;

    for (i = 0; i < n; ++i)
        ((char *)s)[i] = 0;
    }
