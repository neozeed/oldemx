/* strncat.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <string.h>

char *strncat (char *string1, const char *string2, size_t count)
    {
    char *dst;

    dst = string1;
    while (*dst != 0)
        ++dst;
    while (count > 0 && *string2 != 0)
        {
        *dst++ = *string2++;
        --count;
        }
    while (count > 0)
        {
        *dst++ = 0;
        --count;
        }
    *dst = 0;
    return (string1);
    }
