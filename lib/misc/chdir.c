/* chdir.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>
#include <errno.h>

int chdir (const char *name)
    {
    if (__chdir (name) == 0)
        return (0);
    else
        {
        errno = ENOENT;
        return (-1);
        }
    }
