/* perror.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdlib.h>
#include <stdio.h>

void perror (const char *string)
    {
    if (string != NULL && *string != 0)
        {
        (void)fputs (string, stderr);
        (void)fputs (": ", stderr);
        }
    if (errno < 0 || errno > sys_nerr)
        (void)fputs (sys_errlist[sys_nerr], stderr);
    else
        (void)fputs (sys_errlist[errno], stderr);
    fputc ('\n', stderr);
    }
