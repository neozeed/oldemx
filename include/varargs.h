/* varargs.h (emx/gcc) */

#if !defined (_VARARGS_H)
#define _VARARGS_H

#if !defined (NULL)
#define NULL ((void *)0)
#endif

#define _VA_ROUND(type) ((sizeof (type) + 3) & -4)

#define va_alist __builtin_va_alist
#define va_dcl int __builtin_va_alist;
#define va_list char *

#define va_start(alist) alist = (char *)&__builtin_va_alist
#define va_end(alist) alist = NULL
#define va_arg(alist,t) (alist += _VA_ROUND (t), \
                                              *((t *)(alist - _VA_ROUND (t))))

#endif /* !defined (_VARARGS_H) */
