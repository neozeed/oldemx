/* getcwd.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *getcwd (char *buffer, int size)
    {
    char tmp[512], *p;
    int len;

    if (_getcwd (tmp, 0) < 0)
        {
        errno = ERANGE;
        return (NULL);
        }
    len = strlen (tmp) + 2;
    if (len > size)
        {
        errno = ERANGE;
        return (NULL);
        }
    if (buffer == NULL)
        {
        if (size < len) size = len;
        buffer = malloc (size);
        }
    if (buffer == NULL)
        {
        errno = ENOMEM;
        return (NULL);
        }
    for (p = tmp; *p != 0; ++p)
        if (*p == '\\') *p = '/';
    buffer[0] = '/';
    strcpy (buffer+1, tmp);
    }
