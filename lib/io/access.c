/* access.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <errno.h>
#include <io.h>

int access (const char *name, int mode)
    {
    int a;

    a = __chmod (name, 0, 0);
    if (a < 0)
        return (-1);
    if (a & _A_SUBDIR)          /* directories always readable and writable */
        return (0);
    if (a & _A_VOLID)
        {
        errno = ENOENT;
        return (-1);
        }
    if ((mode & 2) && (a & _A_RDONLY))
        {
        errno = EACCES;
        return (-1);
        }
    return (0);
    }
