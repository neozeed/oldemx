/* ftime.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <sys/timeb.h>
#include <time.h>

void ftime (struct timeb *ptr)
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
    ptr->time = mktime (&tm);
    ptr->millitm = dtd.hsec * 10;
    ptr->dstflag = 0;           /* not implemented */
    ptr->timezone = 0;          /* not implemented */
    }
