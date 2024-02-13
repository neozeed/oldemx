/* atexit.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>

int atexit (void (*func)(void))
    {
    if (_atexit_n >= sizeof (_atexit_v) / sizeof (_atexit_v[0]))
        return (-1);
    _atexit_v[_atexit_n++] = func;
    return (0);
    }
