/* _startup.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

static const char _libc_copyright[] = " libc/emx -- Copyright (c) 1990-1992 by Eberhard Mattes ";
static const char _version_warning[] = "WARNING: emx 0.8c or later required\r\n";

void _startup (void)
    {
    int i, j;

    if (_emx_vcmp < 0x302e3863)             /* 0.8c */
        (void)__write (2, _version_warning, strlen (_version_warning));
    __ftime (&_start_time);
    for (i = 0; i < _nfiles; ++i)
        {
        _files[i] = 0;
        _lookahead[i] = -1;
        }
    for (i = 0; i <= 2; ++i)
        {
        _files[i] |= O_TEXT;
        j = __ioctl1 (i, 0);
        if (j < 0 || (j & 0x80))
            _files[i] |= F_DEV;
        }
    for (i = 3; i <_nfiles; ++i)
        _streams[i].flags = 0;
    }
