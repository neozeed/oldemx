/* fseek.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <io.h>
#include <errno.h>

/* Bug: seeking within buffer of read-only file could be optimized */

int fseek (FILE *stream, long offset, int origin)
    {
    long pos;

    if (!(stream->flags & _IOOPEN) || origin < 0 || origin > 2)
        {
        errno = EINVAL;
        return (EOF);
        }
    /* No flush required if: read-only file and new position within buffer */
    /*                       and F_REREAD not set                          */
    (void)fflush (stream);
    stream->flags &= ~_IOEOF;
    if (stream->flags & _IORW)
        stream->flags &= ~(_IOREAD|_IOWRT);
    if (origin == SEEK_CUR)
        {
        pos = ftell (stream);
        if (pos == -1L) return (EOF);
        offset += pos;
        origin = SEEK_SET;
        }
    return ((lseek (stream->handle, offset, origin) == -1L) ? EOF : 0);
    }
