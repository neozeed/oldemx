/* _fbuf.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <stdlib.h>

/* Assign a buffer to a stream (which must not have a buffer) */

void _fbuf (FILE *stream)
    {
    if (stream->flags & _IONBF)
        stream->buffer = NULL;
    else
        stream->buffer = malloc (BUFSIZ);
    if (stream->buffer == NULL)
        {
        stream->buf_size = 1;
        stream->buffer = &stream->char_buf;
        stream->flags &= ~(_IOFBF|_IOLBF|_IOBUFMASK);
        stream->flags |= _IONBF|_IOBUFCHAR;
        }
    else
        {
        stream->buf_size = BUFSIZ;
        stream->flags &= ~_IOBUFMASK;
        stream->flags |= _IOBUFLIB;
        }
    stream->ptr = stream->buffer;
    stream->rcount = 0;
    stream->wcount = 0;
    }
