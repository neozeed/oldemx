/* fclose.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <stdlib.h>

int fclose (FILE *stream)
    {
    int result;
    char buf[32];

    result = EOF;
    if ((stream->flags & F_INUSE) && !(stream->flags & F_STRING))
        {
        result = fflush (stream);
        if (close (fileno (stream)) < 0)
            result = EOF;
        if (result == 0 && (stream->flags & F_TMP))
            {
            itoa (stream->tmpidx, buf, 10);
            if (remove (buf) != 0)
                result = EOF;
            }
        if ((stream->flags & F_BUF_MASK) == F_LIB_BUF)
            free (stream->buffer);
        }
    stream->flags = 0;
    return (result);
    }
