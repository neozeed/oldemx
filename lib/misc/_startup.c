/* _startup.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>

static const char _libc_copyright[] =
    " libc/emx -- Copyright (c) 1990-1992 by Eberhard Mattes ";

static const char _version_warning[] =
    "WARNING: emx 0.8d or later required\r\n";

static char ibuf[BUFSIZ];

void _startup (void)
    {
    int i, j;

    if (_emx_vcmp < 0x302e3864)             /* 0.8d */
        (void)__write (2, _version_warning, strlen (_version_warning));
    __ftime (&_start_time);
    for (i = 0; i < _nfiles; ++i)
        {
        _files[i] = 0;
        _lookahead[i] = -1;
        _streams[i].flags = 0;
        if (ioctl (i, FGETHTYPE, &j) >= 0)
            {
            _files[i] |= O_TEXT;
            if (HT_ISDEV (j))
                _files[i] |= F_DEV;
            if (j == HT_NPIPE)
                _files[i] |= F_NPIPE;
            _streams[i].flags |= _IOOPEN;
            _streams[i].ptr = NULL;
            _streams[i].buffer = NULL;
            _streams[i].rcount = 0;
            _streams[i].wcount = 0;
            _streams[i].handle = i;
            _streams[i].buf_size = 0;
            _streams[i].tmpidx = 0;
            _streams[i].pid = 0;
            switch (i)
                {
                case 0:
                    _files[0] |= O_RDONLY;
                    _streams[0].flags |= _IOREAD | _IOFBF | _IOBUFUSER;
                    _streams[0].ptr = ibuf;
                    _streams[0].buffer = ibuf;
                    _streams[0].buf_size = BUFSIZ;
                    break;
                case 1:
                case 2:
                    _files[i] |= O_WRONLY;
                    _streams[i].flags |= _IOWRT  | _IONBF | _IOBUFNONE;
                    break;
                default:
                    _files[i] |= O_RDWR;
                    _streams[i].flags |= _IORW | _IOFBF | _IOBUFNONE;
                    break;
                }
            }
        }
    }
