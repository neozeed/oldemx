/* setvbuf.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <stdlib.h>

int setvbuf (FILE *stream, char *buffer, int mode, size_t size)
    {
    if (!(stream->flags & F_INUSE) ||
            (mode != _IONBF && mode != _IOFBF && mode != _IOLBF) ||
            (mode != _IONBF && size <= 0))
        return (EOF);
    fflush (stream);
    if ((stream->flags & F_BUF_MASK) == F_LIB_BUF)
        free (stream->buffer);
    stream->flags &= ~(F_BUF_MASK|_IOLBF|_IOFBF|_IONBF);
    if (mode == _IONBF)
        {
        stream->buf_size = 1;
        stream->buffer = &stream->char_buf;
        stream->flags |= _IONBF|F_CHAR_BUF;
        }
    else if (buffer != NULL)
        {
        stream->buf_size = size;
        stream->buffer = buffer;
        stream->flags |= mode|F_USER_BUF;
        }
    else
        {
        buffer = malloc (size);
        if (buffer == NULL)
            return (EOF);
        stream->buf_size = size;
        stream->buffer = buffer;
        stream->flags |= mode|F_LIB_BUF;
        }
    stream->ptr = stream->buffer;
    stream->rcount = 0;
    stream->wcount = 0;
    return (0);
    }
