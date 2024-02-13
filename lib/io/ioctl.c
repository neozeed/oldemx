/* ioctl.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>
#include <sys/termio.h>

int ioctl (int handle, int request, int arg)
    {
    int rc, saved_errno;
    const struct termio *tp;

    saved_errno = errno; errno = 0;
    rc = __ioctl2 (handle, request, arg);
    if (rc >= 0 && errno == 0 && (request == TCSETA || request == TCSETAF
                                                    || request == TCSETAW))
        {
        tp = (const struct termio *)arg;
        if (tp->c_lflag & IDEFAULT)
            _files[handle] &= ~F_TERMIO;
        else
            _files[handle] |= F_TERMIO;
        }
    if (errno == 0)
        errno = saved_errno;
    return (rc);
    }
