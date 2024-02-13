/* tell.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>

long tell (int handle)
    {
    long n;

    if (handle < 0 || handle >= _nfiles)
        {
        errno = EBADF;
        return (-1L);
        }
    n = (long)__lseek (handle, 0L, SEEK_CUR);
    if (n == -1)
        return (n);
    if (_lookahead[handle] >= 0)
        --n;
    return (n);
    }
