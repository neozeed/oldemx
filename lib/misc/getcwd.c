/* getcwd.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/param.h>

char *getcwd (char *buffer, int size)
    {
    char tmp[MAXPATHLEN+1], *p;
    int len;

    if (__getcwd (tmp, 0) < 0)
        return (NULL);
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
    (void)strcpy (buffer+1, tmp);
    return (buffer);
    }
