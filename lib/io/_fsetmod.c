/* _fsetmod.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdio.h>
#include <io.h>
#include <errno.h>
#include <fcntl.h>

int _fsetmode (FILE *stream, const char *mode)
    {
    int i;

    if (*mode == 'b')
        i = O_BINARY;
    else if (*mode == 't')
        i = O_TEXT;
    else
        {
        errno = EINVAL;
        return (-1);
        }
    if (setmode (fileno (stream), i) == -1)
        return (-1);
    return (0);
    }
