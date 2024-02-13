/* eof.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>

int eof (int handle)
    {
    long cur, len;

    if (handle < 0 || handle >= _nfiles)
        {
        errno = EBADF;
        return (-1);
        }
    if (_files[handle] & F_EOF)         /* Ctrl-Z reached */
        return (1);
    cur = tell (handle);
    if (cur < 0)
        return (-1);
    len = filelength (handle);
    if (len < 0)
        return (-1);
    return (cur == len);
    }
