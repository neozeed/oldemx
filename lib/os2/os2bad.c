/* os2bad.c (emx/gcc) */

#include <stdio.h>
#include <stdlib.h>

void _os2_bad (void)
    {
    (void)fputs ("\nOS/2 API call not fixed up\n", stderr);
    exit (2);
    }
