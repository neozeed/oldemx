/* _newstre.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>

FILE *_newstream (void)
    {
    int i;

    for (i = 0; i < _nfiles; ++i)
        if (!(_streams[i].flags & _IOOPEN))
            {
            /* initialize some fields */
            return (&_streams[i]);
            }
    return (NULL);
    }
