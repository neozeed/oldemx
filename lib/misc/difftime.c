/* difftime.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <time.h>

double difftime (time_t t1, time_t t0)
    {
    return ((double)(t1-t0));
    }
