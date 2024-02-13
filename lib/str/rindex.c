/* rindex.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <strings.h>

char *rindex (const char *string, int c)
    {
    int i;

    i = 0;
    while (string[i] != 0) ++i;
    while (i >= 0)
        if (string[i] == (char)c)
            return ((char *)(string+i));
        else
            --i;
    return (NULL);
    }
