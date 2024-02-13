/* unlink.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <io.h>

int unlink (const char *name)
    {
    return (remove (name));                 /* There are no links */
    }
