/* read.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>


/* Bug: removes (in text mode) all CR characters, not only those which */
/*      are followed by a LF character.                                */

int read (int handle, void *buf, size_t nbyte)
    {
    int ret, n, j;
    char *p, *dst, *src;

    if (handle < 0 || handle >= _NFILES)
        {
        errno = EBADF;
        return (-1);
        }
    if (nbyte > 0 && (_files[handle] & F_EOF))
        return (0);
    ret = 0; dst = buf;
redo:
    n = _read (handle, dst, nbyte);
    if (n < 0)
        return (-1);
    if ((_files[handle] & O_TEXT) && !(_files[handle] & _TERMIO) && n > 0)
        {
        p = memchr (dst, 0x1a, n);
        if (p != NULL)
            {
            n = p-dst;
            _files[handle] |= F_EOF;
            }
        src = dst;
        while ((p = memchr (src, '\r', n)) != NULL)
            {
            j = p-src;
            if (dst != src) memcpy (dst, src, j);
            src += j+1; n -= j+1; dst += j; ret += j; nbyte -= j;
            }
        if (n > 0)
            {
            if (dst != src) memcpy (dst, src, n);
            dst += n; ret += n; nbyte -= n;
            }
        if (ret == 0 && nbyte > 0 && !(_files[handle] & F_EOF))
            goto redo;
        }
    else
        return (n);
    return (ret);
    }
