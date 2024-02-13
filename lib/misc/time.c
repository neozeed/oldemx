/* time.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/timeb.h>
#include <time.h>

time_t time (time_t *t)
    {
    struct timeb tb;

    ftime (&tb);
    if (t != NULL) *t = tb.time;
    return (tb.time);
    }
