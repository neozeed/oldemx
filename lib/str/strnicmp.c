/* strnicmp.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <string.h>
#include <ctype.h>

int strnicmp (const char *string1, const char *string2, size_t count)
    {
    int d;

    while (count != 0)
        {
        d = tolower((unsigned char)*string1) -
            tolower((unsigned char)*string2);
        if (d != 0 || *string1 == 0 || *string2 == 0)
            return (d);
        ++string1; ++string2;
        --count;
        }
    return (0);
    }
