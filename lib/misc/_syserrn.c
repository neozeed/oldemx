/* _syserrn.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>

int _syserrno (void)
    {
    return (__syserrno ());
    }
