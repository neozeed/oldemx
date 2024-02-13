/* setvbuf.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <stdlib.h>

int setvbuf (FILE *stream, char *buffer, int mode, size_t size)
    {
    if (!(stream->flags & _IOOPEN) ||
            (mode != _IONBF && mode != _IOFBF && mode != _IOLBF) ||
            (mode != _IONBF && size <= 0))
        return (EOF);
    (void)fflush (stream);
    if ((stream->flags & _IOBUFMASK) == _IOBUFLIB)
        free (stream->buffer);
    stream->flags &= ~(_IOBUFMASK|_IOLBF|_IOFBF|_IONBF);
    if (mode == _IONBF)
        {
        stream->buf_size = 1;
        stream->buffer = &stream->char_buf;
        stream->flags |= _IONBF|_IOBUFCHAR;
        }
    else if (buffer != NULL)
        {
        stream->buf_size = size;
        stream->buffer = buffer;
        stream->flags |= mode|_IOBUFUSER;
        }
    else
        {
        buffer = malloc (size);
        if (buffer == NULL)
            return (EOF);
        stream->buf_size = size;
        stream->buffer = buffer;
        stream->flags |= mode|_IOBUFLIB;
        }
    stream->ptr = stream->buffer;
    stream->rcount = 0;
    stream->wcount = 0;
    return (0);
    }
