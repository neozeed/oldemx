/* write.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define CTRL_Z 0x1a

#define BEGIN do {
#define END   } while (0)

#define WRTBUF BEGIN n = __write (handle, tmp, buf_cnt); \
                     if (n < 0) goto error;              \
                     out_cnt += n;                       \
                     if (n != buf_cnt) {errno = ENOSPC; return (-1);} \
                     buf_cnt = 0;                        \
               END

int write (int handle, const void *buf, size_t nbyte)
    {
    int out_cnt, lf_cnt, i, n, buf_cnt;
    const char *src, *p;
    char tmp[1024];

    if (handle < 0 || handle >= _nfiles)
        {
        errno = EBADF; return (-1);
        }
    if (_files[handle] & O_APPEND)
        (void)__lseek (handle, 0L, SEEK_END);
    if (nbyte == 0)                 /* Avoid truncation of file */
        return (0);
    src = buf;
    if (_files[handle] & O_TEXT)
        {
        out_cnt = lf_cnt = 0;
        buf_cnt = 0;
        p = memchr (src, '\n', nbyte);
        if (p == NULL)
            goto write_bin;
        for (i = 0; i < nbyte; ++i)
            {
            if (src[i] == '\n')
                {
                if (buf_cnt >= sizeof (tmp)) WRTBUF;
                tmp[buf_cnt++] = '\r';
                ++lf_cnt;
                }
            if (buf_cnt >= sizeof (tmp)) WRTBUF;
            tmp[buf_cnt++] = src[i];
            }
        if (buf_cnt != 0) WRTBUF;
        return (out_cnt - lf_cnt);
        }

write_bin:
    n = __write (handle, src, nbyte);
    if (n < 0) goto error;
    if (n == 0 && !((_files[handle] & F_DEV) && *src == CTRL_Z))
        {
        errno = ENOSPC;
        return (-1);
        }
    return (n);

error:
    return (-1);
    }
