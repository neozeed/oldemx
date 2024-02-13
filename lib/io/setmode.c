/* setmode.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>
#include <fcntl.h>

int setmode (int handle, int mode)
    {
    int old_mode;

    if (handle < 0 || handle >= _NFILES)
        {
        errno = EBADF;
        return (-1);
        }
    if (mode != O_BINARY && mode != O_TEXT)
        {
        errno = EINVAL;
        return (-1);
        }
    old_mode = _files[handle] & (O_BINARY|O_TEXT);
    _files[handle] = (_files[handle] & ~(O_BINARY|O_TEXT)) | mode;
    return (old_mode);
    }
