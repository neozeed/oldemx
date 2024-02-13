/* remove.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>

int remove (const char *name)
    {
    return (_remove (name));
    }
