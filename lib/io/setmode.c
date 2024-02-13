/* setmode.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>
#include <fcntl.h>

int setmode (int handle, int mode)
    {
    int old_mode;

    if (handle < 0 || handle >= _nfiles)
        {
        errno = EBADF;
        return (-1);
        }
    old_mode = ((_files[handle] & O_TEXT) ? O_TEXT : O_BINARY);
    if (mode == O_BINARY)
        _files[handle] &= ~O_TEXT;
    else if (mode == O_TEXT)
        _files[handle] |= O_TEXT;
    else
        {
        errno = EINVAL;
        return (-1);
        }
    return (old_mode);
    }
