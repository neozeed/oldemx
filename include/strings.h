/* strings.h (emx/gcc) */

#if !defined (_STRINGS_H)
#define _STRINGS_H

#include <string.h>

int  bcmp (const void *buffer1, const void *buffer2, size_t n);
void bcopy (const void *src, void *dst, size_t n);
void bzero (void *buffer, size_t n);
char *index (const char *string, int c);
char *rindex (const char *string, int c);

#endif /* !defined (_STRINGS_H) */
