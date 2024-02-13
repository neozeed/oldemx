/* ftell.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>

/* Bug: incorrect result with text mode */
/* Bug: does not work with rw files(?) */

long ftell (FILE *stream)
    {
    long pos;
    char *p;

    pos = lseek (stream->handle, 0L, SEEK_CUR);
    if (pos < 0)
        return (-1L);
    if (stream->flags & _IOWRT)
        {
        if (bbuf (stream))
            return (pos + (stream->ptr - stream->buffer));
        else
            return (pos);
        }
    else
        return (pos - stream->rcount);           /* ungetc! */
    }
