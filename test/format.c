/* format.c */

#include <stdio.h>
#include <string.h>

int main ()
    {
    int n, a, b;
    char *fmt = "%d %d";

    for (;;)
        {
        printf ("fmt=\"%s\": ", fmt);
        n = scanf (fmt, &a, &b);
        printf ("n=%d a=%d b=%d\n", n, a, b);
        if (feof (stdin))
            break;
        }
    return (0);
    }
