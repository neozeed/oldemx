/* perror.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdlib.h>
#include <stdio.h>

void perror (const char *string)
    {
    if (string != NULL && *string != 0)
        {
        fputs (string, stderr);
        fputs (": ", stderr);
        }
    if (errno < 0 || errno > sys_nerr)
        fputs (sys_errlist[sys_nerr], stderr);
    else
        fputs (sys_errlist[errno], stderr);
    fputc ('\n', stderr);
    }
