/* stdio.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <fcntl.h>

static char ibuf[BUFSIZ];

struct _stdio _streams[_NFILES] =
    {
        {ibuf, ibuf, 0, 0, 0, _IOOPEN|_IOREAD|_IOFBF|_IOBUFUSER, BUFSIZ, 0, 0},
        {NULL, NULL, 0, 0, 1, _IOOPEN|_IOWRT |_IONBF|_IOBUFNONE, 0,      0, 0},
        {NULL, NULL, 0, 0, 2, _IOOPEN|_IOWRT |_IONBF|_IOBUFNONE, 0,      0, 0}
    };
