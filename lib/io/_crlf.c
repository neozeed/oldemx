/* _crlf.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <io.h>
#include <string.h>

int _crlf (char *buf, size_t size, size_t *new_size)
    {
    size_t n, j, ret;
    char *p, *dst, *src;

    src = buf; dst = buf; n = size; ret = 0;
    while ((p = memchr (src, '\r', n)) != NULL)
        {
        j = p - src;
        if (dst != src)
            (void)memmove (dst, src, j);
        src += j+1; n -= j+1; dst += j; ret += j;
        }
    if (n > 0)
        {
        if (dst != src)
            (void)memmove (dst, src, n);
        ret += n;
        }
    *new_size = ret;
    return (0);
    }
