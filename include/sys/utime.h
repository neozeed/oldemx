/* sys/utime.h (emx/gcc) */

#if !defined (_TIME_T_DEFINED)
#define _TIME_T_DEFINED
typedef long time_t;
#endif

#if !defined (_UTIMBUF_DEFINED)
#define _UTIMBUF_DEFINED
struct utimbuf
    {
    time_t actime;
    time_t modtime;
    };
#endif

int utime (const char *name, const struct utimbuf *times);
