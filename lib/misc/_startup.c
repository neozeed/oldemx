/* _startup.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>

static char _libc_copyright[] = " libc/emx -- Copyright (c) 1990-1992 by Eberhard Mattes ";

void _startup (void)
    {
    int i, j;

    _time (&_start_time);
    for (i = 0; i <= 2; ++i)
        {
        j = _ioctl1 (i, 0);
        if (j < 0 || (j & 0x80))
            {
            _files[i] |= F_DEV;
            _streams[i].flags |= F_DEV;
            }
        }
    }
