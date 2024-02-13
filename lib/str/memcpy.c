/* memcpy.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <string.h>

void *memcpy (void *s1, const void *s2, int n)
    {
    int i;
  
    for (i = 0; i < n; ++i)
        ((char *)s1)[i] = ((char *)s2)[i];
    return (s1);
    }
