/* sys/timeb.h (emx/gcc) */

#if !defined (_SYS_TIMEB_H)
#define _SYS_TIMEB_H

#if !defined (_TIME_T_DEFINED)
#define _TIME_T_DEFINED
typedef long time_t;
#endif

struct timeb
    {
    time_t time;
    unsigned short millitm;
    short timezone;
    short dstflag;
    };

void ftime (struct timeb *ptr);

#endif /* !defined (_SYS_TIMEB_H) */
