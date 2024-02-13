/* string.h (emx/gcc) */

#if !defined (_STRING_H)
#define _STRING_H

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

char *strcat (char *string1, const char *string2);
char *strchr (const char *string, int c);
int strcmp (const char *string1, const char *string2);
char *strcpy (char *string1, const char *string2);
size_t strcspn (const char *string1, const char *string2);
char *strdup (const char *string);
char *strerror (int errnum);
int stricmp (const char *string1, const char *string2);
size_t strlen (const char *string);
char *strlwr (char *string);
char *strncat (char *string1, const char *string2, size_t count);
int strncmp (const char *string1, const char *string2, size_t count);
char *strncpy (char *string1, const char *string2, size_t count);
int strnicmp (const char *string1, const char *string2, size_t count);
char *strnset (char *string, int c, size_t count);
char *strpbrk (const char *string1, const char *string2);
char *strrchr (const char *string, int c);
char *strrev (char *string);
char *strset (char *string, int c);
size_t strspn (const char *string1, const char *string2);
char *strstr (const char *string1, const char *string2);
char *strtok (char *string1, const char *string2);
char *strupr (char *string);

size_t _memcount (const void *mem, int c, size_t n);

#endif /* !defined (_STRING_H) */
