/* wait.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>
#include <process.h>
#include <errno.h>

int wait (int *term)
    {
    int dummy, rc;

    if (term == NULL)
        term = &dummy;
    rc = _wait (term);
    if (rc == -1)
        errno = ECHILD;
    return (rc);
    }
