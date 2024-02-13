/* clock.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <time.h>

static time_t start = -1;

clock_t clock (void)
    {
    struct tm tm;

    if (start == -1)
        {
        tm.tm_sec = _start_time.sec;
        tm.tm_min = _start_time.min;
        tm.tm_hour = _start_time.hour;
        tm.tm_mday = _start_time.day;
        tm.tm_mon = _start_time.month-1;
        tm.tm_year = _start_time.year - 1900;
        tm.tm_isdst = 0;
        start = mktime (&tm);
        }
    return (CLOCKS_PER_SEC * (time (NULL) - start));
    }
