/* _isterm.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>

int _isterm (int handle)
    {
    int j;

    if (!isatty (handle))
        return (0);
    j = __ioctl1 (handle, 0);
    if (j < 0)
        return (0);
    return ((j & 0x03) ? 1 : 0);
    }
