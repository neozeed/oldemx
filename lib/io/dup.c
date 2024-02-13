/* dup.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>

int dup (int handle)
    {
    int new;

    new = __dup (handle);
    if (new < 0)
        return (new);
    if (new >= _nfiles)
        {
        __close (new);
        errno = EMFILE;
        return (-1);
        }
    _files[new] = _files[handle];
    _lookahead[new] = _lookahead[handle];
    return (new);
    }
