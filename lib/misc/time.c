/* time.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <time.h>

time_t time (time_t *t)
    {
    struct tm tm;
    struct _dtd dtd;
    time_t t0;

    _time (&dtd);
    tm.tm_sec = dtd.sec;
    tm.tm_min = dtd.min;
    tm.tm_hour = dtd.hour;
    tm.tm_mday = dtd.day;
    tm.tm_mon = dtd.month-1;
    tm.tm_year = dtd.year - 1900;
    tm.tm_isdst = 0;
    t0 = mktime (&tm);
    if (t != NULL) *t = t0;
    return (t0);
    }
