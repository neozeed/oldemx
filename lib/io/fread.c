/* fread.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <stdlib.h>                     /* min */
#include <io.h>
#include <errno.h>
#include <string.h>

size_t fread (void *buffer, size_t size, size_t count, FILE *stream)
    {
    size_t total, left, n;
    int r;   /* signed! */
    char *dst;
    int fh, c;

    if (size == 0 || count == 0)
        return (0);
    total = size * count;
    if (total / count != size)
        {
        errno = ERANGE;
        return ((size_t)EOF);
        }
    if (nbuf (stream))
        _fbuf (stream);
    left = total;
    dst = buffer;
    fh = fileno (stream);
    stream->flags |= _IOREAD;
    if (bbuf (stream))
        while (left != 0)
            {
            if (stream->rcount != 0)
                {
                n = min ((size_t)stream->rcount, left);
                memcpy (dst, stream->ptr, n);
                stream->ptr += n;
                stream->rcount -= n;
                dst += n;
                left -= n;
                }
            else if (left > BUFSIZ)
                {
                n = (left / BUFSIZ) * BUFSIZ;      /* Number of buffers */
                r = read (fh, dst, n);
                if (r < 0)
                    {
                    stream->flags |= _IOERR;
                    break;
                    }
                if (r == 0)
                    {
                    stream->flags |= _IOEOF;
                    break;
                    }
                left -= r;
                dst += r;
                }
            else
                {
                c = _fill (stream);
                if (c == EOF)
                    break;
                *dst++ = (char)c;
                --left;
                }
            }
    else
        {
        if (stream->rcount != 0)
            {
            n = min ((size_t)stream->rcount, left);
            memcpy (dst, stream->ptr, n);
            stream->ptr += n;
            stream->rcount -= n;
            dst += n;
            left -= n;
            }
        while (left != 0)
            {
            r = read (fh, dst, left);
            if (r < 0)
                {
                stream->flags |= _IOERR;
                break;
                }
            if (r == 0)
                {
                stream->flags |= _IOEOF;
                break;
                }
            dst += r;
            left -= r;
            }
        }
    return ((total - left) / size);
    }
