/* gettimeo.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <sys/time.h>
#include <time.h>

int gettimeofday (struct timeval *tp, struct timezone *tzp)
    {
    struct tm tm;
    struct _dtd dtd;

    __ftime (&dtd);
    tm.tm_sec = dtd.sec;
    tm.tm_min = dtd.min;
    tm.tm_hour = dtd.hour;
    tm.tm_mday = dtd.day;
    tm.tm_mon = dtd.month-1;
    tm.tm_year = dtd.year - 1900;
    tm.tm_isdst = 0;
    if (tp != NULL)
        {
        tp->tv_sec = mktime (&tm);
        tp->tv_usec = dtd.hsec * 10000;
        }
    if (tzp != NULL)
        {
        tzp->tz_minuteswest = 0;        /* not implemented */
        tzp->tz_dsttime = 0;            /* not implemented */
        }
    return (0);
    }
