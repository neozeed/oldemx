/* fflush.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>

int fflush (FILE *stream)
    {
    int result, n;
    long pos;

    result = 0;
    if ((stream->flags & _IOWRT) && bbuf (stream))
        {
        n = stream->ptr - stream->buffer;
        if (n > 0 && write (fileno (stream), stream->buffer, n) <= 0)
            {
            stream->flags |= _IOERR;
            result = EOF;
            }
        }
    if ((stream->flags & _IOREAD) && bbuf (stream) && !isatty (fileno (stream)))
        {
        pos = ftell (stream);
        if (pos == -1L)
            result = EOF;
        else if (lseek (fileno (stream), pos, SEEK_SET) == EOF)
            result = EOF;
        }
    stream->ptr = stream->buffer;
    stream->rcount = 0;
    stream->wcount = 0;
    stream->flags &= ~F_REREAD;     /* Undo ungetc */
    return (result);
    }
