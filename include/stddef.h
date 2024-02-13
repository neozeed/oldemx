/* stddef.h (emx/gcc) */

#if !defined (_STDDEF_H)
#define _STDDEF_H

typedef long ptrdiff_t;

#if !defined (_SIZE_T)
#define _SIZE_T
typedef unsigned int size_t;
#endif

#if !defined (NULL)
#define NULL ((void *)0)
#endif

#endif
