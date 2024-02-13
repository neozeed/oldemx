/* strchr.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <string.h>

char *strchr (const char *string, int c)
    {
    do
        {
        if (*string == (char)c)
            return ((char *)string);
        } while (*string++ != 0);
    return (NULL);
    }
