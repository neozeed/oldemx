/* _getdriv.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>

char _getdrive (void)
    {
    return (__getdrive ());
    }
