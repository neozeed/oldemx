/* time.h (emx/gcc) */

#if !defined (_SIZE_T)
#define _SIZE_T
typedef unsigned int size_t;
#endif

#if !defined (NULL)
#define NULL ((void *)0)
#endif

#if !defined (_TIME_T_DEFINED)
#define _TIME_T_DEFINED
typedef long time_t;
#endif

#if !defined (_CLOCK_T_DEFINED)
#define _CLOCK_T_DEFINED
typedef long clock_t;
#endif

#if !defined (_TM_DEFINED)
#define _TM_DEFINED
struct tm
    {
    int tm_sec;     /* 0..59 */
    int tm_min;     /* 0..59 */
    int tm_hour;    /* 0..23 */
    int tm_mday;    /* 1..31 */
    int tm_mon;     /* 0..11 */
    int tm_year;    /* 0(:=1990).. */
    int tm_wday;    /* 0..6 */
    int tm_yday;    /* 0..365 */
    int tm_isdst;   /* 0 */
    };
#endif

#if !defined (CLOCKS_PER_SEC)
#define CLOCKS_PER_SEC 100
#define CLK_TCK 100
#endif

double difftime (time_t t1, time_t t0);
char *asctime (const struct tm *t);
char *ctime (const time_t *t);
clock_t clock (void);
struct tm *gmtime (const time_t *t);
struct tm *localtime (const time_t *t);
time_t mktime (struct tm *t);
size_t strftime (char *string, size_t size, const char *format,
                 const struct tm *t);
time_t time (time_t *t);
