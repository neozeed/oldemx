/* _fill.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <errno.h>

int _fill (FILE *stream)
    {
    if (!(stream->flags & F_INUSE) || (stream->flags & F_STRING))
        {
        errno = EACCES;
        return (EOF);
        }
    if (stream->flags & _IOWRT)         /* File in write mode? */
        {
        stream->flags |= _IOERR;
        errno = EACCES;
        return (EOF);
        }
    stream->flags |= _IOREAD;          /* Switch to read mode */
    stream->wcount = 0;
    stream->flags &= ~F_REREAD;        /* Buffer empty, no reread required */
    if (nbuf (stream))
        _fbuf (stream);
    else
        stream->ptr = stream->buffer;
    stream->rcount = read (fileno (stream), stream->buffer, stream->buf_size);
    if (stream->rcount == 0)
        {
        stream->flags |= _IOEOF;
        return (EOF);
        }
    if (stream->rcount < 0)
        {
        stream->flags |= _IOERR;
        stream->rcount = 0;
        return (EOF);
        }
    --stream->rcount;
    return ((unsigned char)*stream->ptr++);
    }
