/* strncmp.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <string.h>

int strncmp (const char *string1, const char *string2, size_t count)
    {
    int d;

    while (count != 0)
        {
        d = (int)(unsigned char)*string1 - (int)(unsigned char)*string2;
        if (d != 0 || *string1 == 0 || *string2 == 0)
            return (d);
        ++string1; ++string2;
        --count;
        }
    return (0);
    }
