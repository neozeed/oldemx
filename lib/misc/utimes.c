/* utimes.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/utime.h>

int utime (const char *name, const struct utimbuf *times)
    {
    struct _ftd ftd;
    struct tm *tm;
    int handle, result;
    struct utimbuf now;

    handle = open (name, O_WRONLY);
    if (handle < 0)
        return (-1);            /* open sets errno */
    if (times == NULL)
        {
        (void)time (&now.modtime);
        times = &now;
        }
    tm = gmtime (&times->modtime);
    ftd.sec = tm->tm_sec;
    ftd.min = tm->tm_min;
    ftd.hour = tm->tm_hour;
    ftd.day = tm->tm_mday;
    ftd.month = tm->tm_mon+1;
    ftd.year = tm->tm_year + 1900 - 1980;
    if (__filetime (handle, 1, &ftd) < 0)
        {
        result = -1;
        errno = EACCES;             /* ??? */
        }
    else
        result = 0;
    (void)close (handle);
    return (result);
    }


int utimes (const char *name, const struct timeval *tvp)
    {
    struct utimbuf ut;

    ut.actime = tvp[0].tv_sec;
    ut.modtime = tvp[1].tv_sec;
    return (utime (name, &ut));
    }
