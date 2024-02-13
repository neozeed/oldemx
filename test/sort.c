/* sort.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE  1

static int qcmp (const void *p1, const void *p2)
    {
    return (strcmp (*(char **)p1, *(char **)p2));
    }

static void usage (void)
    {
    fputs ("Usage: sort [-c]\n", stderr);
    exit (1);
    }

static int elements;
static int allocated;
static char **vector;

int main (int argc, char *argv[])
    {
    char buffer[512], *p;
    char check;
    FILE *f;
    int i;

    check = FALSE;
    for (i = 1; i < argc; ++i)
        {
        if (argv[i][0] != '-')
            break;
        if (strcmp (argv[i]+1, "c") == 0)
            check = TRUE;
        else
            usage ();
        }
    if (i == argc)
        f = stdin;
    else if (i+1 == argc)
        {
        f = fopen (argv[i], "rt");
        if (f == NULL)
            {
            fputs ("Cannot open input file\n", stderr);
            return (1);
            }
        }
    else
        usage();
    elements = 0; allocated = 0; vector = NULL;
    while (!feof (f))
        {
        if (fgets (buffer, sizeof (buffer), f) == NULL)
            break;
        p = strchr (buffer, '\n');
        if (p != NULL) *p = 0;
        if (elements >= allocated)
            {
            allocated += 1000;
            vector = (char **)realloc (vector, allocated * sizeof (char *));
            if (vector == NULL)
                {
                fputs ("Out of memory\n", stderr);
                return (2);
                }
            }
        p = strdup (buffer);
        if (p == NULL)
            {
            fputs ("Out of memory\n", stderr);
            return (2);
            }
        vector[elements++] = p;
        }
    if (ferror (f))
        {
        fputs ("Error reading input file\n", stderr);
        return (2);
        }
    fprintf (stderr, "%d line%s read\n", elements, (elements == 1 ? "" : "s"));
    qsort (vector, elements, sizeof (char *), qcmp);
    for (i = 0; i < elements; ++i)
        if (puts (vector[i]) == EOF)
            {
            fputs ("Error writing output file\n", stderr);
            return (2);
            }
    if (check)
        {
        for (i = 1; i < elements; ++i)
            if (strcmp (vector[i-1], vector[i]) > 0)
                fprintf (stderr, "Internal error, i=%d\n", i);
        }
    return (0);
    }
