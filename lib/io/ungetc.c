/* ungetc.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <errno.h>

int ungetc (int c, FILE *stream)
    {
    if (!(stream->flags & _IOOPEN) || c == EOF)
        return (EOF);
    if (stream->flags & _IOSTRING)
        {
        /* ungetc on a string is used only by scanf, and this does an */
        /* ungetc of the recently read character, so we don't have to */
        /* write it to the (read-only!) string.                       */
        --stream->ptr;
        ++stream->rcount;
        stream->flags &= ~_IOEOF;
        return ((unsigned char)c);
        }
    if (!(stream->flags & _IOREAD))      /* File in read mode? */
        {
        stream->flags |= _IOERR;
        errno = EACCES;
        return (EOF);
        }
    if (nbuf (stream))
        _fbuf (stream);
    if (stream->ptr == stream->buffer)
        {
        if (stream->rcount != 0)
            return (EOF);               /* multiple ungetc: no space */
        *stream->ptr = (char)c;
        }
    else
        {
        --stream->ptr;
        *stream->ptr = (char)c;
        }
    ++stream->rcount;
    stream->flags &= ~_IOEOF;
    stream->flags |= _IOREREAD;         /* for fseek */
    return ((unsigned char)c);
    }
