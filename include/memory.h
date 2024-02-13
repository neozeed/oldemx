/* memory.h (emx/gcc) */

#if !defined (_MEMORY_H)
#define _MEMORY_H

#if !defined (_SIZE_T_DEFINED)
#define _SIZE_T_DEFINED
typedef unsigned long size_t;
#endif

#if !defined (NULL)
#define NULL ((void *)0)
#endif

void *memccpy (void *s1, const void *s2, int c, size_t n);
void *memchr (const void *s, int c, size_t n);
int memcmp (const void *s1, const void *s2, size_t n);
void *memcpy (void *s1, const void *s2, size_t n);
int memicmp (const void *s1, const void *s2, size_t n);
void *memmove (void *s1, const void *s2, size_t n);
void *memset (void *s, int c, size_t n);

size_t _memcount (const void *mem, int c, size_t n);

#endif /* !defined (_MEMORY_H) */
