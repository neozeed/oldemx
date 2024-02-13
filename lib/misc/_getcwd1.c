/* _getcwd1.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>

int _getcwd1 (char *buffer, char drive)
    {
    char *p;

    if (__getcwd (buffer+1, drive) < 0)
        return (-1);
    for (p = buffer; *p != 0; ++p)
        if (*p == '\\') *p = '/';
    buffer[0] = '/';
    return (0);
    }
