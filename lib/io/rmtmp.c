/* rmtmp.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>

int rmtmp (void)
    {
    int i, n;

    n = 0;
    for (i = 0; i < _nfiles; ++i)
        if ((_streams[i].flags & _IOOPEN) && (_streams[i].flags & _IOTMP))
            if (fclose (&_streams[i]) == 0)
                ++n;
    return (n);
    }
