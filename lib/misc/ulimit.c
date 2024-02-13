/* ulimit.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>
#include <errno.h>

#define UL_GFILLIM 1
#define UL_SFILLIM 2
#define UL_GMEMLIM 3
#define UL_NOFILES 4

long ulimit (int cmd, long newlimit)
    {
    switch (cmd)
        {
        case UL_GFILLIM:
            return (1 << 21);
        case UL_SFILLIM:
            return (newlimit);
        case UL_GMEMLIM:
            return (__ulimit (cmd, newlimit));
        case UL_NOFILES:
            return (40);
        default:
            errno = EINVAL;
            return (-1);
        }
    }
