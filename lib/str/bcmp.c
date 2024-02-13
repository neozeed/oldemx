/* bcmp.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <strings.h>

int bcmp (const void *s1, const void *s2, int n)
    {
    int i, d;
    
    for (i = 0; i < n; ++i)
        {
        d = (int)((unsigned char *)s1)[i] - (int)((unsigned char *)s2)[i];
        if (d != 0)
            {
            if (d > 0)
                return (1);
            else
                return (-1);
            }
        }
    return (0);
    }
