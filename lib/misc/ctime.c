/* ctime.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <time.h>

char *ctime (const time_t *t)
    {
    struct tm *x;

    x = localtime (t);
    if (x == NULL)
        return (NULL);
    else
        return (asctime (x));
    }
