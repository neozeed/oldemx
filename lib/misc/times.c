/* times.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <time.h>
#include <sys/times.h>

long times (struct tms *buffer)
    {
    buffer->tms_utime = clock () / CLOCKS_PER_SEC;
    buffer->tms_stime = 0;
    buffer->tms_cutime = 0;
    buffer->tms_cstime = 0;
    return (0);
    }
