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
        __close (two_handles[0]);
        __close (two_handles[1]);
        errno = EMFILE;
        return (-1);
        }
    _files[two_handles[0]] = O_RDONLY;
    _files[two_handles[1]] = O_WRONLY;
    return (0);
    }
