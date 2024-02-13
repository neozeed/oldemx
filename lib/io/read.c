/* read.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

/* Read nbyte characters, use lookahead, if available. This is simple unless */
/* O_NDELAY is in effect. */

static int read_lookahead (int handle, void *buf, size_t nbyte)
    {
    int i, n, saved_errno;
    char *dst;

    i = 0; dst = buf; saved_errno = errno;
    if (nbyte > 0 && _lookahead[handle] != -1)
        {
        *dst = (char)_lookahead[handle];
        _lookahead[handle] = -1;
        ++i; --nbyte;
        }
    n = __read (handle, dst+i, nbyte);
    if (n == -1)
        {
        if (errno == EAGAIN && i > 0)           /* lookahead and O_NDELAY */
            {
            errno = saved_errno;                /* hide EAGAIN */
            return (i);                         /* and be successful */
            }
        return (-1);
        }
    return (i + n);
    }


int read (int handle, void *buf, size_t nbyte)
    {
    int n;
    size_t j;
    char *dst, c;

    if (handle < 0 || handle >= _nfiles)
        {
        errno = EBADF;
        return (-1);
        }
    if (nbyte > 0 && (_files[handle] & F_EOF))
        return (0);
    dst = buf;
    n = read_lookahead (handle, dst, nbyte);
    if (n == -1)
        return (-1);
    if ((_files[handle] & O_TEXT) && !(_files[handle] & F_TERMIO) && n > 0)
        {
        /* special processing for text mode */
        if (!(_files[handle] & (F_NPIPE|F_DEV)) && dst[n-1] == 0x1a &&
                                                   eof (handle))
            {
            /* remove last Ctrl-Z in text files */
            --n;
            _files[handle] |= F_EOF;
            if (n == 0)
                return (0);
            }
        if (n == 1 && dst[0] == '\r')
            {
            /* This is the tricky case as we are not allowed to decrement n  */
            /* by one as 0 indicates end of file. We have to use look ahead. */
            int saved_errno = errno;
            j = read_lookahead (handle, &c, 1); /* look ahead */
            if (j == -1 && errno == EAGAIN)
                {
                _lookahead[handle] = dst[0];
                return (-1);
                }
            errno = saved_errno;                /* hide error */
            if (j == 1 && c == '\n')            /* CR/LF ? */
                dst[0] = '\n';                  /* yes -> replace with LF */
            else
                _lookahead[handle] = c;         /* no -> save the 2nd char */
            }
        else if (_crlf (dst, n, &n))            /* CR/LF conversion */
            _lookahead[handle] = '\r';          /* buffer ends with CR */
        }
    return (n);
    }
