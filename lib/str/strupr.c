/* strupr.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <string.h>
#include <ctype.h>

char *strupr (char *string)
    {
    unsigned char *p;

    for (p = (unsigned char *)string; *p != 0; ++p)
        if (islower (*p))
            *p = (unsigned char)_toupper (*p);
    return (string);
    }
