/* sys/time.h (emx/gcc) */

#include <time.h>

#if !defined (_TIMEVAL_DEFINED)
#define _TIMEVAL_DEFINED
struct timeval
    {
    long tv_sec;
    long tv_usec;
    };
#endif

int utimes (const char *name, const struct timeval *tvp);
