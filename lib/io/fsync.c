/* fsync.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>

int fsync (int handle)
    {
    return (__fsync (handle));
    }
