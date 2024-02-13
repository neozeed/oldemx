/* strerror.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdlib.h>

char *strerror (int errnum)
    {
    if (errnum < 0 || errnum > sys_nerr)
        return ((char *)sys_errlist [sys_nerr]);
    else
        return ((char *)sys_errlist [errnum]);
    }
