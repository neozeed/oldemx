/* strdup.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <string.h>
#include <stdlib.h>

char *strdup (const char *string)
    {
    char *p;

    p = malloc (strlen (string) + 1);
    if (p != NULL)
        strcpy (p, string);
    return (p);
    }
