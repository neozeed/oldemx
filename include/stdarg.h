/* stdarg.h (emx/gcc) */

#if !defined (_STDARG_H)
#define _STDARG_H

#if !defined (_VA_LIST_DEFINED)
#define _VA_LIST_DEFINED
typedef char *va_list;
#endif

#if !defined (NULL)
#define NULL ((void *)0)
#endif

#define _VA_ROUND(t) ((sizeof (t) + 3) & -4)

#if !defined (va_start)
#define va_start(ap,v) ap = (va_list)&v + ((sizeof (v) + 3) & -4)
#define va_arg(ap,t) (ap += _VA_ROUND (t), *(t *)(ap - _VA_ROUND (t)))
#define va_end(ap) ap = NULL
#endif

#endif /* !defined (_STDARG_H) */
