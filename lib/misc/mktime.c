/* mktime.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <time.h>

time_t mktime (struct tm *t)
    {
    time_t x;
    struct tm *tmp;

    if (t->tm_sec < 0 || t->tm_min < 0 || t->tm_hour < 0 ||
        t->tm_mday < 0 || t->tm_mon < 0 || t->tm_year < 0)
        return ((time_t)-1);
    if (t->tm_mon >= 12)
        {
        t->tm_year += (t->tm_mon / 12);
        t->tm_mon %= 12;        /* _mktime wants 0 <= tm_mon <= 11 */
        }
    x = (time_t)_mktime (t);
    tmp = localtime (&x);
    if (tmp == NULL)
        return ((time_t)-1);
    else
        *t = *tmp;
    return (x);
    }


/* year >= 1582, 1 <= month <= 12, 1 <= day <= 31 */
/* source: emclib */

int _day (int year, int month, int day)
    {
    int result;

    if (year < 1582)
        return (-1);
    result = 365*year + day + 31*(month-1);
    if (month <= 2)
        {
        result += (year-1) / 4;
        result -= (3*((year-1)/100+1)) / 4;
        }
    else
        {
        result -= (4*month+23) / 10;
        result += year / 4;
        result -= (3*(year/100+1)) / 4;
        }
    return (result);
    }


int _mktime (struct tm *t)
    {
    int result;

    result = _day (t->tm_year+1900, t->tm_mon+1, t->tm_mday);
    if (result < 0)
        return (-1);
    result -= _day (1970, 1, 1);
    result *= 24*60*60;
    result += t->tm_sec + 60*t->tm_min + 60*60*t->tm_hour;
    return (result);
    }
