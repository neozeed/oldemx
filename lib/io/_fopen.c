/* _fopen.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <errno.h>

FILE *_fopen (FILE *dst, const char *fname, const char *mode)
    {
    char ok, bt;
    int omode;

    switch (*mode)
        {
        case 'r':
            dst->flags = _IOREAD;
            omode = O_RDONLY;
            break;
        case 'w':
            dst->flags = _IOWRT;
            omode = O_WRONLY|O_CREAT|O_TRUNC;
            break;
        case 'a':
            dst->flags = _IOWRT;
            omode = O_WRONLY|O_CREAT|O_APPEND;
            break;
        default:
            errno = EINVAL;
            return (NULL);
        }
    ++mode; ok = TRUE; bt = FALSE;
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
                    omode |= O_TEXT;
                    }
                break;
            case 'b':
                if (bt)
                    ok = FALSE;
                else
                    {
                    bt = TRUE;
                    omode |= O_BINARY;
                    }
                break;
            case '+':
                if (dst->flags & _IORW)
                    ok = FALSE;
                else
                    {
                    omode &= ~(O_RDONLY|O_WRONLY);
                    omode |= O_RDWR;
                    dst->flags &= ~(_IOREAD|_IOWRT);
                    dst->flags |= _IORW;
                    }
                break;
            default:
                ok = FALSE; break;
            }
        if (ok) ++mode;
        }
    dst->handle = open (fname, omode, umask (0));
    if (dst->handle < 0)
        return (NULL);
    dst->ptr = NULL;
    dst->buffer = NULL;
    dst->rcount = 0;
    dst->wcount = 0;
    dst->tmpidx = 0;
    dst->flags |= _IOOPEN | _IOBUFNONE;
    return (dst);
    }
