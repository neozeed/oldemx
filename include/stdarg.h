/* stdarg.h */

#if !defined (_VA_LIST_DEFINED)
#define _VA_LIST_DEFINED
typedef char *va_list;
#endif

#if !defined (va_start)
#define va_start(ap,v) ap = (va_list)&v + sizeof (v)
#define va_arg(ap,t) ((t *)(ap += sizeof (t)))[-1]
#define va_end(ap) ap = NULL
#endif
