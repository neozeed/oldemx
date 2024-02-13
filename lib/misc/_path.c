/* _path.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <errno.h>

int _path (char *dst, const char *name)
    {
    if (strpbrk (name, "/\\:") != NULL)
        {
        if (access (name, 4) == 0)
            strcpy (dst, name);
        else
            dst[0] = 0;
        }
    else
        {
        _searchenv (name, "EMXPATH", dst);
        if (dst[0] == 0)
            _searchenv (name, "PATH", dst);
        }
    if (dst[0] == 0)
        {
        errno = ENOENT;
        return (-1);
        }
    return (0);
    }
