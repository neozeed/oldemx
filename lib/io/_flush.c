/* _flush.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <errno.h>

int _flush (int c, FILE *stream)
    {
    int n, w, fh;
    char ch;

    if (!(stream->flags & F_INUSE) || (stream->flags & F_STRING))
        {
        errno = EACCES;
        return (EOF);
        }
    if (stream->flags & _IOREAD)    /* File in read mode? */
        {
        stream->flags |= _IOERR;
        errno = EACCES;
        return (EOF);
        }
    fh = fileno (stream);
    stream->flags |= _IOWRT;        /* Switch to write mode */
    stream->rcount = 0;
    stream->flags &= ~_IOEOF;       /* Clear EOF flag, writing! */
    stream->wcount = 0;             /* Maybe negative at this point */
    if (nbuf (stream))
        _fbuf (stream);
    if (bbuf (stream))
        {
        n = stream->ptr - stream->buffer;
        if (n > 0)                  /* n should never be < 0 */
            w = write (fh, stream->buffer, n);
        else                        /* New or flushed buffer */
            {
            w = 0;
            if (stream->flags & O_APPEND)
                lseek (fh, 0L, SEEK_END);
            }
        stream->ptr = stream->buffer;
        *stream->ptr++ = (char)c;
        stream->wcount = stream->buf_size - 1;
        }
    else
        {
        n = 1;
        ch = (char)c;
        w = write (fh, &ch, 1);
        stream->wcount = 0;
        }

    if (n != w)
        {
        stream->flags |= _IOERR;
        return (EOF);
        }
    return ((unsigned char)c);
    }
