/* umask.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>

int umask (int pmode)
    {
    return (__umask (pmode));
    }
