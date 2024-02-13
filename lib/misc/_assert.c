/* _assert.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#undef NDEBUG

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void _assert (char *string, char *fname, unsigned int line)
    {
    fprintf (stderr, "Assertion failed: %s, file %s, line %u\n",
                     string, fname, line);
    fflush (stderr);
    abort ();
    }
