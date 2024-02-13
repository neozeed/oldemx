/* isatty.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>

int isatty (int handle)
    {
    if (handle < 0 || handle >= _NFILES)
        {
        errno = EBADF;
        return (0);
        }
    else
        return ((_files[handle] & F_DEV) ? 1 : 0);
    }
