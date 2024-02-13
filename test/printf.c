/* printf.c */

#include <stdio.h>

int main()
    {
    char buf[100];

    for (;;)
        {
        if (fgets (buf, sizeof (buf), stdin) == NULL)
            {
            perror ("fgets"); return (1);
            }
        printf (buf, 1);
        printf (buf, -1);
        printf (buf, 1234);
        printf (buf, -1234);
        }
    }
