/* strpbrk.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <string.h>

char *strpbrk (const char *string1, const char *string2)
    {
    char table[256];

    memset (table, 1, 256);
    while (*string2 != 0)
        table[(unsigned char)*string2++] = 0;
    table[0] = 0;
    while (table[(unsigned char)*string1])
        ++string1;
    return (*string1 == 0 ? NULL : (char *)string1);
    }
