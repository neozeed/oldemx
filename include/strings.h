/* strings.h (emx/gcc) */

#include <string.h>

int  bcmp (const void *buffer1, const void *buffer2, int size);
void bcopy (const void *src, void *dst, int size);
void bzero (void *buffer, int size);
char *index (const char *string, int c);
char *rindex (const char *string, int c);
