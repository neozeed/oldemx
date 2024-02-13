/* strcpy.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <string.h>

char *strcpy (char *string1, const char *string2)
    {
    char *dst;

    dst = string1;
    while ((*dst = *string2) != 0)
        ++dst, ++string2;
    return (string1);
    }
