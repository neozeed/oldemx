/* stdio.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <fcntl.h>

const int _nfile = _NFILE;
static char ibuf[BUFSIZ];

struct _stdio _streams[_NFILE] =
    {
        {ibuf, ibuf, 0, 0, 0, F_INUSE|_IOREAD|_IOFBF|F_USER_BUF, BUFSIZ, 0, 0},
        {NULL, NULL, 0, 0, 1, F_INUSE|_IOWRT |_IONBF|F_NO_BUF,   0,      0, 0},
        {NULL, NULL, 0, 0, 2, F_INUSE|_IOWRT |_IONBF|F_NO_BUF,   0,      0, 0}
    };
