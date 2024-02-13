/* fclose.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>

int fclose (FILE *stream)
    {
    int result;
    char buf[32];

    result = EOF;
    if ((stream->flags & _IOOPEN) && !(stream->flags & _IOSTRING))
        {
        result = 0;
        result = fflush (stream);
        if (close (fileno (stream)) < 0)
            result = EOF;
        if (result == 0 && (stream->flags & _IOTMP))
            {
            (void)itoa (stream->tmpidx, buf, 10);
            if (remove (buf) != 0)
                result = EOF;
            }
        if ((stream->flags & _IOBUFMASK) == _IOBUFLIB)
            free (stream->buffer);
        }
    stream->flags = 0;
    return (result);
    }
