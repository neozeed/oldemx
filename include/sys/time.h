/* sys/time.h (emx/gcc) */

#if !defined (_SYS_TIME_H)
#define _SYS_TIME_H

#include <time.h>

#if !defined (_TIMEVAL_DEFINED)
#define _TIMEVAL_DEFINED
struct timeval
    {
    long tv_sec;
    long tv_usec;
    };
#endif

#if !defined (_TIMEZONE_DEFINED)
#define _TIMEZONE_DEFINED

struct timezone
    {
    int tz_minuteswest;
    int tz_dsttime;
    };
#endif

int utimes (const char *name, const struct timeval *tvp);
int gettimeofday (struct timeval *tp, struct timezone *tzp);
int settimeofday (const struct timeval *tp, const struct timezone *tzp);

#endif /* !defined (_SYS_TIME_H) */
