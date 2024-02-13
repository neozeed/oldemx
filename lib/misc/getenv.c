/* getenv.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdlib.h>
#include <string.h>

char *getenv (const char *name)
    {
    int len;
    char **p, *s;

    if (name == NULL || environ == NULL)
        return (NULL);
    len = strlen (name);
    for (p = environ; *p != NULL; ++p)
        {
        s = *p;
        if (strlen (s) > len && s[len] == '=' && (memcmp (name, s, len) == 0))
            return (s + len + 1);
        }
    return (NULL);
    }
