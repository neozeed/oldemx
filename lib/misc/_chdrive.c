/* _chdrive.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>

int _chdrive (char drive)
    {
    return (__chdrive (drive));
    }
