/* spawnvp.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stddef.h>
#include <process.h>

int spawnvp (int mode, const char *name, const char * const *argv)
    {
    return (spawnvpe (mode, name, argv, NULL));
    }
