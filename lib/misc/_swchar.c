/* _swchar.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>

char _swchar (void)
    {
    int x;

    x = __swchar (0, 0);
    if (x & 0xff)
        return (0);
    else
        return ((char)((x>>8) & 0xff));
    }
