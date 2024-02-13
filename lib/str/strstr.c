/* strstr.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <string.h>

char *strstr (const char *string1, const char *string2)
    {
    int len1, len2, i;
    char first;

    len1 = 0;
    while (string1[len1] != 0) ++len1;
    len2 = 0;
    while (string2[len2] != 0) ++len2;
    if (len2 == 0)
        return ((char *)(string1+len1));
    first = *string2;
    while (len1 >= len2)
        {
        if (*string1 == first)
            {
            for (i = 1; i < len2; ++i)
                if (string1[i] != string2[i])
                    break;
            if (i >= len2)
                return ((char *)string1);
            }
        ++string1; --len1;
        }
    return (NULL);
    }
