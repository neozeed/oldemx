/* fdopen.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <errno.h>

/* Bug: doesn't check for compatible modes (O_ACCMODE) */

FILE *fdopen (int handle, const char *mode)
    {
    char ok, bt;
    FILE *dst;
    int omode;

    if (handle < 0 || handle >= _nfiles)
        {
        errno = EBADF;
        return (NULL);
        }
    dst = _newstream ();
    switch (*mode)
        {
        case 'r':
            dst->flags = _IOREAD;
            break;
        case 'w':
            dst->flags = _IOWRT;
            break;
        case 'a':
            dst->flags = _IOWRT;
            break;
        default:
            return (NULL);
        }
    ++mode; ok = TRUE; bt = FALSE; omode = 0;
    while (*mode != 0 && ok)
        {
        switch (*mode)
            {
            case 't':
                if (bt)
                    ok = FALSE;
                else
                    {
                    bt = TRUE;
                    omode = O_TEXT;
                    }
                break;
            case 'b':
                if (bt)
                    ok = FALSE;
                else
                    {
                    bt = TRUE;
                    omode = O_BINARY;
                    }
                break;
            case '+':
                if (dst->flags & _IORW)
                    ok = FALSE;
                else
                    {
                    dst->flags &= ~(_IOREAD|_IOWRT);
                    dst->flags |= _IORW;
                    }
                break;
            default:
                ok = FALSE; break;
            }
        if (ok) ++mode;
        }
    if (bt)
        (void)setmode (handle, omode);
    dst->handle = handle;
    dst->ptr = NULL;
    dst->buffer = NULL;
    dst->rcount = 0;
    dst->wcount = 0;
    dst->flags |= _IOOPEN | _IOBUFNONE;
    return (dst);
    }
