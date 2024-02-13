/* spawnv.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stddef.h>
#include <process.h>

int spawnv (int mode, const char *name, const char * const *argv)
    {
    return (spawnve (mode, name, argv, NULL));
    }
