/* memccpy.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <string.h>

void *memccpy (void *s1, const void *s2, int c, int n)
    {
    int i;
  
    for (i = 0; i < n; ++i)
        {
        if ((((char *)s1)[i] = ((char *)s2)[i]) == (char)c)
            return ((char *)s1+i+1);
        }
    return (NULL);
    }
