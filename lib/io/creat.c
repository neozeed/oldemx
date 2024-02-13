/* creat.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <io.h>
#include <fcntl.h>

int creat (const char *name, int pmode)
    {
    return (open (name, O_WRONLY|O_TRUNC|O_CREAT, pmode));
    }
