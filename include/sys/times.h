/* sys/times.h (emx/gcc) */

#if !defined (_SYS_TIMES_H)
#define _SYS_TIMES_H

struct tms
    {
    time_t tms_utime;
    time_t tms_stime;
    time_t tms_cutime;
    time_t tms_cstime;
    };
#endif

long times (struct tms *buffer);
