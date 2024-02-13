/* os2test.c (emx/gcc) */

#include <stdio.h>
#include <string.h>
#include <os2.h>

char upper_case[]="upper case";

int main (void)
    {
    COUNTRYCODE cc;
    ULONG aul[100];
    ULONG cb, i, rc;
    CHAR ach[256];

    cc.country = 0;
    cc.codepage = 0;
    if ((rc = DosMapCase (strlen (upper_case), &cc, upper_case)) != 0)
        (void)printf ("DosMapCase failed: %lu\n", rc);
    else
        (void)printf ("DosMapCase: %s\n", upper_case);
    if ((rc = DosQueryCp (sizeof (aul), aul, &cb)) != 0)
        (void)printf ("DosQueryCp failed: %lu\n", rc);
    else
        {
        (void)printf ("Code pages:");
        for (i = 0; i < cb / sizeof (aul[0]); ++i)
            (void)printf (" %lu", aul[i]);
        (void)fputchar ('\n');
        }
    if ((rc = DosQueryCollate (sizeof (ach), &cc, ach, &cb)) != 0)
        (void)printf ("DosQueryCollate failed: %lu\n", rc);
    else
        {
        (void)printf ("DosQueryCollate:");
        for (i = 0; i < cb / sizeof (ach[0]); ++i)
            (void)printf (" %d", (int)(UCHAR)ach[i]);
        (void)fputchar ('\n');
        }
    return (0);
    }
