/* bcopy.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <strings.h>

void bcopy (const void *s1, void *s2, int n)
    {
    int i;

    if ((size_t)s1 < (size_t)s2)
        for (i = n-1; i >= 0; --i)
            ((char *)s2)[i] = ((char *)s1)[i];
    else
        for (i = 0; i < n; ++i)
            ((char *)s2)[i] = ((char *)s1)[i];
    }
