/* tell.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <io.h>

long tell (int handle)
    {
    return (lseek (handle, 0L, SEEK_CUR));
    }
