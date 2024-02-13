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
    int ret, n, more;
    size_t j;
    char *p, *dst;

    if (handle < 0 || handle >= _nfiles)
        {
        errno = EBADF;
        return (-1);
        }
    if (nbyte > 0 && (_files[handle] & F_EOF))
        return (0);
    ret = 0; dst = buf;
    if (nbyte > 0 && _lookahead[handle] != -1)
        {
        *dst++ = (char)_lookahead[handle];
        _lookahead[handle] = -1;
        ++ret; --nbyte;
        }
redo:
    n = __read (handle, dst, nbyte);
    if (n < 0)
        return (-1);
    if ((_files[handle] & O_TEXT) && !(_files[handle] & F_TERMIO) && n > 0)
        {
        p = memchr (dst, 0x1a, n);
        if (p != NULL)
            {
            n = p - dst;
            _files[handle] |= F_EOF;
            }
        more = _crlf (dst, n, &j);
        ret += j; nbyte -= j; dst += j;
        if (more)
            {
            /* ... */
            }
        if (ret == 0 && nbyte > 0 && !(_files[handle] & F_EOF))
            goto redo;
        }
    else
        return (n);
    return (ret);
    }
