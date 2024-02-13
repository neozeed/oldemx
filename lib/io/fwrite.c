/* fwrite.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <io.h>
#include <errno.h>
#include <string.h>

size_t fwrite (const void *buffer, size_t size, size_t count, FILE *stream)
    {
    size_t total, left, n;
    int w;   /* signed! */
    const char *src;
    int fh;

    if (size == 0 || count == 0)
        return (0);
    total = size * count;
    if (total / count != size)
        {
        errno = ERANGE;
        return ((size_t)EOF);
        }
    if (stream->flags & _IOREAD)    /* File in read mode? */
        {
        stream->flags |= _IOERR;
        errno = EACCES;
        return ((size_t)EOF);
        }
    if (nbuf (stream))
        _fbuf (stream);
    left = total;
    src = buffer;
    fh = fileno (stream);
    stream->flags |= _IOWRT;
    if (bbuf (stream))
        {
        if (stream->wcount == 0 && stream->ptr == stream->buffer)
            stream->wcount = stream->buf_size;
        while (left != 0)
            {
            if (left <= stream->wcount)
                {
                memcpy (stream->ptr, src, left);
                stream->ptr += left;
                stream->wcount -= left;
                src += left;
                left = 0;
                }
            else if (stream->ptr != stream->buffer) /* Buffer non-empty */
                {
                n = stream->ptr - stream->buffer;
                stream->ptr = stream->buffer;
                while (n != 0)
                    {
                    w = write (fh, stream->ptr, n);
                    if (w <= 0)
                        {
                        stream->flags |= _IOERR;
                        goto done;
                        }
                    n -= w; stream->ptr += w;
                    }
                stream->ptr = stream->buffer;
                stream->wcount = stream->buf_size;
                }
            else
                {
                w = write (fh, src, left);
                if (w <= 0)
                    {
                    stream->flags |= _IOERR;
                    goto done;
                    }
                src += w;
                left -= w;
                }
            }
        }
    else
        while (left != 0)
            {
            w = write (fh, src, left);
            if (w <= 0)
                {
                stream->flags |= _IOERR;
                goto done;
                }
            src += w;
            left -= w;
            }
done:
    return ((total - left) / size);
    }
