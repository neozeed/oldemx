/* args.c */

#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[], char *envp[])
    {
    int i;

    _response (&argc, &argv);
    _wildcard (&argc, &argv);
    printf ("argc=%d\n\n", argc);
    for (i = 0; i < argc; ++i)
        printf ("argv[%d]=\"%s\"\n", i, argv[i]);
    printf ("\nEnvironment:\n");
    for (i = 0; envp[i] != NULL; ++i)
        printf ("envp[%d]=\"%s\"\n", i, envp[i]);
    return (0);
    }
