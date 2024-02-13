/* stricmp.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <string.h>
#include <ctype.h>

int stricmp (const char *string1, const char *string2)
    {
    int d;

    for (;;)
        {
        d = tolower((unsigned char)*string1) -
            tolower((unsigned char)*string2);
        if (d != 0 || *string1 == 0 || *string2 == 0)
            return (d);
        ++string1; ++string2;
        }
    }
