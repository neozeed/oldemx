/* memory.c */

#include <stdio.h>
#include <string.h>

int main (void)
    {
    char buf1[] = "this is a test string";
    char *p;
    int n;

    n = strlen (buf1);
    p = memchr (buf1, 'x', n);
    if (p != NULL) puts ("error 1");
    p = memchr (buf1, ' ', 0);
    if (p != NULL) puts ("error 2");
    p = memchr (buf1, 't', n);
    if (p != buf1) puts ("error 3");
    p = memchr (buf1, 't', 0);
    if (p != NULL) puts ("error 4");
    p = memchr (buf1, 'g', n);
    if (p != buf1+n-1) puts ("error 5");
    p = memchr (buf1, 's', 3);
    if (p != NULL) puts ("error 6");
    p = memchr (buf1, 's', 4);
    if (p != buf1+3) puts ("error 7");
    puts ("done");
    return (0);
    }
