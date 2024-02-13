/* stdio.c */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
    {
    FILE *f;
    int i, j;

    if (argc != 2)
        {
        fputs ("Usage: stdio <output_file>\n", stderr);
        return (1);
        }
    f = fopen (argv[1], "wb");
    if (f == NULL)
        {
        fputs ("fopen() failed\n", stderr);
        return (1);
        }
    for (i = 0; i < 32768; ++i)
        {
        if (fwrite (&i, sizeof (i), 1, f) != 1)
            {
            fputs ("fwrite() failed\n", stderr);
            return (1);
            }
        if (i % 4111 == 0) fflush (f);
        if (ftell (f) != (i+1) * sizeof (i))
            {
            fputs ("ftell() buggy\n", stderr);
            return (1);
            }
        }
    if (fflush (f) != 0)
        {
        fputs ("fflush() failed\n", stderr);
        return (1);
        }
    fclose (f);
    f = fopen (argv[1], "rb");
    if (f == NULL)
        {
        fputs ("fopen() failed\n", stderr);
        return (1);
        }
    for (i = 0; i < 32768; ++i)
        {
        if (fread (&j, sizeof (j), 1, f) != 1)
            {
            fputs ("fread() failed\n", stderr);
            return (1);
            }
        if (i != j)
            {
            fputs ("Mismatch\n", stderr);
            return (1);
            }
        if (i % 4111 == 0) fflush (f);
        if (ftell (f) != (i+1) * sizeof (i))
            {
            fputs ("ftell() buggy\n", stderr);
            return (1);
            }
        }
    fclose (f);
    return (0);
    }

