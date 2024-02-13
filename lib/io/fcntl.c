/* fcntl.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <fcntl.h>
#include <errno.h>

#define FLAGS (O_APPEND | O_NDELAY)

int fcntl (int handle, int request, int arg)
    {
    if (handle < 0 || handle >= _nfiles)
        {
        errno = EBADF;
        return (-1);
        }
    switch (request)
        {
        case F_GETFL:
            return (_files[handle] & FLAGS);
        case F_SETFL:
            if (arg & ~FLAGS)
                break;
            if (__fcntl (handle, request, arg) == -1)
                return (-1);
            SETBITS (_files[handle], FLAGS, arg);
            return (0);
        case F_GETFD:
        case F_SETFD:
            return (__fcntl (handle, request, arg));
        }
    errno = EINVAL;
    return (-1);
    }
