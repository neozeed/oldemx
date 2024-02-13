/* stddef.h (emx/gcc) */

#if !defined (_STDDEF_H)
#define _STDDEF_H

typedef long ptrdiff_t;

#if !defined (_SIZE_T_DEFINED)
#define _SIZE_T_DEFINED
typedef unsigned long size_t;
#endif

#if !defined (NULL)
#define NULL ((void *)0)
#endif

#endif /* !defined (_STDDEF_H) */
