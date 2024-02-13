/* truncate.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <io.h>
#include <fcntl.h>

int truncate (char *name, long length)
    {
    int handle, result;

    handle = open (name, O_RDWR);
    if (handle < 0)
        return (-1);
    result = ftruncate (handle, length);
    (void)close (handle);
    return (result);
    }
