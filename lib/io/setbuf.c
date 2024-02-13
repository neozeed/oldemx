/* setbuf.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>

void setbuf (FILE *stream, char *buffer)
    {
    fflush (stream);
    if ((stream->flags & F_BUF_MASK) == F_LIB_BUF)
        free (stream->buffer);
    stream->flags &= ~(F_BUF_MASK|_IONBF|_IOLBF|_IOFBF);
    if (buffer == NULL)
        {
        stream->flags |= _IONBF|F_CHAR_BUF;
        stream->buf_size = 1;
        stream->buffer = &stream->char_buf;
        }
    else
        {
        stream->flags |= _IOFBF|F_USER_BUF;
        stream->buf_size = BUFSIZ;
        stream->buffer = buffer;
        }
    stream->ptr = stream->buffer;
    stream->rcount = 0;
    stream->wcount = 0;
    }
