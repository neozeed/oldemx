/* dup2.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>

int dup2 (int handle1, int handle2)
    {
    if (handle2 < 0)
        {
        errno = EINVAL;
        return (-1);
        }
    if (handle2 >= _nfiles)
        {
        errno = EMFILE;
        return (-1);
        }
    if (__dup2 (handle1, handle2) < 0)
        return (-1);
    _files[handle2] = _files[handle1];
    _lookahead[handle2] = _lookahead[handle1];
    return (handle2);
    }
