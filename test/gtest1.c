/* gtest1.c */

#include <io.h>

static char x, c;
int a,b;
char *p;

int main()
    {

    p="test!";
    write(1,p,5);
    x = (a == b);
    x += '0';
    write(1,&x,1);
    a = p[c];
    b = p[(unsigned char)c];
    exit(2);
    return (0);
    }
