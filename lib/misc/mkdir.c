/* mkdir.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>
#include <errno.h>

int mkdir (const char *name)
    {
    if (__mkdir (name) == 0)
        return (0);
    else
        {
        errno = ENOENT;
        return (-1);
        }
    }
