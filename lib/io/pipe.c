/* pipe.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>
#include <fcntl.h>

int pipe (int *two_handles)
    {
    if (__pipe (two_handles, 8192) != 0)
        return (-1);
    if (two_handles[0] >= _nfiles || two_handles[1] >= _nfiles)
        {
        (void)__close (two_handles[0]);
        (void)__close (two_handles[1]);
        errno = EMFILE;
        return (-1);
        }
    _files[two_handles[0]] = O_RDONLY | F_NPIPE;
    _files[two_handles[1]] = O_WRONLY | F_NPIPE;
    _lookahead[two_handles[0]] = -1;
    _lookahead[two_handles[1]] = -1;
    return (0);
    }
