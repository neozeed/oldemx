/* rename.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <errno.h>

int rename (const char *old_name, const char *new_name)
    {
    return (__rename (old_name, new_name));
    }
