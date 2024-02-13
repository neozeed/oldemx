/* ftruncat.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>

int ftruncate (int handle, int length)
    {
    long n;

    if (handle < 0 || handle >= _NFILES || (_files[handle] & F_DEV))
        {
        errno = EBADF;
        return (-1);
        }
    n = lseek (handle, (long)length, SEEK_SET);
    if (n < 0)
        return (-1);
    if (n != length)
        {
        errno = ERANGE;
        return (-1);
        }
    if (_write (handle, "", 0) != 0)
        {
        errno = EACCES;
        return (-1);
        }
    return (0);
    }
