/* strlwr.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <string.h>
#include <ctype.h>

char *strlwr (char *string)
    {
    unsigned char *p;

    for (p = (unsigned char *)string; *p != 0; ++p)
        if (isupper (*p))
            *p = (unsigned char)_tolower (*p);
    return (string);
    }
