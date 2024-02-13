/* setbuf.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <stdlib.h>

void setbuf (FILE *stream, char *buffer)
    {
    fflush (stream);
    if ((stream->flags & _IOBUFMASK) == _IOBUFLIB)
        free (stream->buffer);
    stream->flags &= ~(_IOBUFMASK|_IONBF|_IOLBF|_IOFBF);
    if (buffer == NULL)
        {
        stream->flags |= _IONBF|_IOBUFCHAR;
        stream->buf_size = 1;
        stream->buffer = &stream->char_buf;
        }
    else
        {
        stream->flags |= _IOFBF|_IOBUFUSER;
        stream->buf_size = BUFSIZ;
        stream->buffer = buffer;
        }
    stream->ptr = stream->buffer;
    stream->rcount = 0;
    stream->wcount = 0;
    }
