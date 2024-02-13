/* ftruncat.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>

int ftruncate (int handle, long length)
    {
    if (handle < 0 || handle >= _nfiles || (_files[handle] & F_DEV))
        {
        errno = EBADF;
        return (-1);
        }
    return (__ftruncate (handle, length));
    }
