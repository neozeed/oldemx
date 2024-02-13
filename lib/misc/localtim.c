/* localtim.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <time.h>

struct tm *localtime (const time_t *t)
    {
    return (gmtime (t));
    }
