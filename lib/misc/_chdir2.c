/* _chdir2.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>
#include <errno.h>

int _chdir2 (const char *name)
    {
    char old_drive, new_drive;

    old_drive =_getdrive ();
    new_drive = _fngetdrive (name);
    if (new_drive != 0 && _chdrive (new_drive) != 0)
        return (-1);
    if (__chdir (name) == 0)
        return (0);
    else
        {
        (void)_chdrive (old_drive);
        errno = ENOENT;
        return (-1);
        }
    }
