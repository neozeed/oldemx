/* _tmpbuf.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>

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
        stream->flags &= ~(_IONBF|_IOLBF|_IOFBF|F_BUF_MASK|_IOEOF);
        if (isatty (fileno (stream)))
            stream->flags |= _IOFBF|F_TMP_BUF;
        else
            stream->flags |= _IOFBF|F_USER_BUF;
        }
    }

void _endbuf (FILE *stream)
    {
    if ((stream->flags & F_BUF_MASK) == F_TMP_BUF)
        {
        fflush (stream);
        stream->buf_size = 1;
        stream->ptr = stream->buffer = &stream->char_buf;
        stream->flags &= ~(_IOFBF|_IOLBF|F_BUF_MASK);
        stream->flags |= _IONBF|F_CHAR_BUF;
        stream->rcount = stream->wcount = 0;
        }
    }
