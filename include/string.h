/* string.h (emx/gcc) */

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

char *strcat (char *string1, const char *string2);
char *strchr (const char *string, int c);
int strcmp (const char *string1, const char *string2);
char *strcpy (char *string1, const char *string2);
size_t strcspn (const char *string1, const char *string2);
char *strdup (const char *string);
char *strerror (int errnum);
int stricmp (const char *string1, const char *string2);
int strlen (const char *string);
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
