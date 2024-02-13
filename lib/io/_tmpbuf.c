/* _tmpbuf.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <io.h>

static char stdout_buf[BUFSIZ];
static char stderr_buf[BUFSIZ];

void _tmpbuf (FILE *stream)
    {
    char *buf;

    if ((stream->flags & _IONBF) && (nbuf (stream) || cbuf (stream)) &&
                (stream == stdout || stream == stderr))
        {
        buf = (stream == stdout ? stdout_buf : stderr_buf);
        stream->ptr = stream->buffer = buf;
        stream->wcount = BUFSIZ;
        stream->rcount = 0;
        stream->flags |= _IOWRT;
        stream->flags &= ~(_IONBF|_IOLBF|_IOFBF|_IOBUFMASK|_IOEOF);
        if (isatty (fileno (stream)))
            stream->flags |= _IOFBF|_IOBUFTMP;
        else
            stream->flags |= _IOFBF|_IOBUFUSER;
        }
    }

void _endbuf (FILE *stream)
    {
    if ((stream->flags & _IOBUFMASK) == _IOBUFTMP)
        {
        (void)fflush (stream);
        stream->buf_size = 1;
        stream->ptr = stream->buffer = &stream->char_buf;
        stream->flags &= ~(_IOFBF|_IOLBF|_IOBUFMASK);
        stream->flags |= _IONBF|_IOBUFCHAR;
        stream->rcount = stream->wcount = 0;
        }
    }
