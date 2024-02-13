/* close.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>

int close (int handle)
    {
    if (handle < 0 || handle >= _NFILES)
        {
        errno = EBADF;
        return (-1);
        }
    return (_close (handle));
    }
