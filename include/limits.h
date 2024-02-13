/* limits.h (emx/gcc) */

#if !defined (_LIMITS_H)
#define _LIMITS_H

#define CHAR_BIT      8
#define SCHAR_MIN   (-128)
#define SCHAR_MAX     127
#define UCHAR_MAX     0xff
#if defined (__CHAR_UNSIGNED__)
#define CHAR_MIN      0
#define CHAR_MAX      UCHAR_MAX
#else
#define CHAR_MIN      SCHAR_MIN
#define CHAR_MAX      SCHAR_MAX
#endif
#define MB_LEN_MAX    1
#define SHRT_MIN    (-32768)
#define SHRT_MAX      32767
#define USHRT_MAX     0xffff
#define LONG_MIN    (-2147483648)
#define LONG_MAX      2147483647
#define ULONG_MAX     0xffffffff
#define INT_MIN       LONG_MIN
#define INT_MAX       LONG_MAX
#define UINT_MAX      ULONG_MAX

#endif /* !defined (_LIMITS_H) */
