struct
    {
    char a;
    unsigned short b;
    char c, d;
    long e;
    } x;

int main ()
    {
    x.b = x.a;
    x.e = x.c;
    return (0);
    }
