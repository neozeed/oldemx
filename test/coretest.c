/* coretest.c (emx/gcc) */

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define INITIALIZED 314159265

static int initialized = 0;
static char *p = NULL;

int main (void)
    {
    int fh, rc;

    (void)printf ("initialized = %d\n", initialized);
    if (initialized == 0)
        {
        initialized = INITIALIZED;
        p = malloc (100);
        (void)strcpy (p, "Hello!");
        fh = open ("coretest.cor", O_WRONLY|O_CREAT|O_TRUNC, S_IREAD|S_IWRITE);
        if (fh < 0)
            (void)printf ("Cannot create core file\n");
        else
            {
            rc = _core (fh);
            if (rc < 0)
                perror ("core");
            (void)close (fh);
            }
        }
    else if (initialized == INITIALIZED)
        {
        (void)printf ("%s\n", p);
        }
    return (0);
    }
