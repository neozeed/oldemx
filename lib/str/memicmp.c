/* memicmp.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <string.h>
#include <ctype.h>

int memicmp (const void *s1, const void *s2, int n)
    {
    int i, d;
    
    for (i = 0; i < n; ++i)
        {
        d = tolower (((unsigned char *)s1)[i]) -
            tolower (((unsigned char *)s2)[i]);
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
