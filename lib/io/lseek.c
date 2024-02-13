/* lseek.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>

long lseek (int handle, long offset, int origin)
    {
    long n, cur;

    if (handle < 0 || handle >= _nfiles)
        {
        errno = EBADF;
        return (-1L);
        }
    if (offset < 0)
        {
        /* DOS doesn't return an error for seek before beginning of file */
        if (origin == SEEK_SET)
            {
            errno = EINVAL;
            return (-1L);
            }
        cur = (long)__lseek (handle, 0L, SEEK_CUR);
        if (cur < 0)
            {
            errno = EBADF;
            return (-1L);
            }
        n = (long)__lseek (handle, 0L, origin);
        if (n + offset < 0)
            {
            (void)__lseek (handle, cur, SEEK_SET);
            errno = EINVAL;
            return (-1L);
            }
        }
    n = (long)__lseek (handle, offset, origin);
    if (n < 0)
        {
        errno = EBADF;
        return (-1L);
        }
    else
        {
        _files[handle] &= ~F_EOF;       /* Clear Ctrl-Z flag */
        return (n);
        }
    }
