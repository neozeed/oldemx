/* gmtime.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <time.h>
#include <stdlib.h>

static __inline__ int leap (unsigned int y)
    {
    return (y % 4 != 0 ? 0 : y % 100 != 0 ? 1 : y % 400 != 0 ? 0 : 1);
    }


struct tm *gmtime (const time_t *t)
    {
    static struct tm result;
    time_t t0, t1;
    div_t q;
    static int mon_len[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    t0 = *t;
    if (t0 < 0) return (NULL);
    q = div (t0, 60); result.tm_sec = q.rem; t0 = q.quot;
    q = div (t0, 60); result.tm_min = q.rem; t0 = q.quot;
    q = div (t0, 24); result.tm_hour = q.rem; t0 = q.quot;
    result.tm_wday = (t0+4) % 7;     /* 01-Jan-1970 was Thursday, ie, 4 */
    result.tm_year = 70;             /* 1970 */
    while (t0 >= 0)
        {
        t1 = t0;
        t0 -= (leap (result.tm_year+1900) ? 366 : 365);
        ++result.tm_year;
        }
    t0 = t1; --result.tm_year;
    result.tm_mon = 0;
    result.tm_yday = t0;
    while (t0 >= 0)
        {
        t1 = t0;
        if (result.tm_mon == 1)       /* February */
            t0 -= (leap (result.tm_year+1900) ? 29 : 28);
        else
            t0 -= mon_len[result.tm_mon];
        ++result.tm_mon;
        }
    t0 = t1; --result.tm_mon;
    result.tm_mday = t0 + 1;
    result.tm_isdst = 0;
    return (&result);
    }
