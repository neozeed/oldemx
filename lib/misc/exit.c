/* exit.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#define _EXIT_C

#include <sys/emx.h>
#include <stdlib.h>

void (*_atexit_v[32])(void);
int _atexit_n = 0;

void volatile exit (int ret)
    {
    int i;

    for (i = _atexit_n-1; i >= 0; --i)
        _atexit_v[i]();
    _cleanup ();
    _exit (ret);
    }
