/* chmod.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

int chmod (const char *name, int pmode)
    {
    int attr, rc;

    attr = __chmod (name, 0, 0);           /* Get attributes */
    if (attr < 0)
        return (-1);
    if (pmode & S_IWRITE)
        attr &= ~1;
    else
        attr |= 1;
    rc = __chmod (name, 1, attr);
    if (rc >= 0) rc = 0;
    return (rc);
    }
