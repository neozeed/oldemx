/* memory.h (emx/gcc) */

#if !defined (_SIZE_T)
#define _SIZE_T
typedef unsigned int size_t;
#endif

#if !defined (NULL)
#define NULL ((void *)0)
#endif

void *memccpy (void *s1, const void *s2, int c, int n);
void *memchr (const void *s, int c, int n);
int memcmp (const void *s1, const void *s2, int n);
void *memcpy (void *s1, const void *s2, int n);
int memicmp (const void *s1, const void *s2, int n);
void *memmove (void *s1, const void *s2, int n);
void *memset (void *s, int c, int n);
