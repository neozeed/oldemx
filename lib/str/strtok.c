/* strtok.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <string.h>

char *strtok (char *string1, const char *string2)
    {
    char table[256];
    unsigned char *p, *result;
    static unsigned char *next = NULL;

    if (string1 != NULL)
        p = (unsigned char *)string1;
    else
        {
        if (next == NULL)
            return (NULL);
        p = next;
        }
    memset (table, 0, 256);
    while (*string2 != 0)
        table[(unsigned char)*string2++] = 1;
    table[0] = 0;
    while (table[*p])
        ++p;
    result = p;
    table[0] = 1;
    while (!table[*p])
        ++p;
    if (*p == 0)
        {
        if (p == result)
            {
            next = NULL;
            return (NULL);
            }
        }
    else
        *p++ = 0;
    next = p;
    return ((char *)result);
    }
