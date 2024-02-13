/* ioctl.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/termio.h>
#include <sys/ioctl.h>
#include <errno.h>

int ioctl (int handle, int request, ...)
    {
    va_list va;
    int rc, saved_errno, arg, *int_ptr;
    const struct termio *tp;

    if (handle < 0 || handle >= _nfiles)
        {
        errno = EBADF;
        return (-1);
        }
    saved_errno = errno; errno = 0;
    va_start (va, request);
    arg = va_arg (va, int);
    va_end (va);
    rc = __ioctl2 (handle, request, arg);
    if (rc >= 0 && errno == 0)
        switch (request)
            {
            case TCSETAF:
            case TCSETAW:
            case TCSETA:
                va_start (va, request);
                tp = va_arg (va, const struct termio *);
                va_end (va);
                if (tp->c_lflag & IDEFAULT)
                    _files[handle] &= ~F_TERMIO;
                else
                    _files[handle] |= F_TERMIO;
                break;
            case FIONREAD:
                if (_lookahead[handle] >= 0)
                    {
                    va_start (va, request);
                    int_ptr = va_arg (va, int *);
                    va_end (va);
                    ++(*int_ptr);
                    }
                break;
            }
    if (errno == 0)
        errno = saved_errno;
    return (rc);
    }
