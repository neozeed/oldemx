/* retcode.c */

#include <stdlib.h>

int main (int argc, char *argv[])
    {
    int i;

    if (argc != 2)
        return (1);
    else
        return (atoi (argv[1]));
    }
