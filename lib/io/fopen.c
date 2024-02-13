/* fopen.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>

FILE *fopen (const char *fname, const char *mode)
    {
    FILE *f;

    f = _newstream ();
    if (f != NULL)
        f = _fopen (f, fname, mode);
    return (f);
    }
