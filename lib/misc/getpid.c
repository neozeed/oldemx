/* getpid.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>

int getpid (void)
    {
    return (__getpid ());
    }
