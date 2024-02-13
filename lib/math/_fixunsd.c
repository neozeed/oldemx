/* _fixunsd.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdio.h>
#include <math.h>

#ifdef USE_FLOATING_POINT

long int __fixunsdfsi (double a)
    {
    if (a < 2147483648.0)
        return ((long)a);
    else
        return (((long)(a - 2147483648.0)) + 2147483648);
    }

#else

long int __fixunsdfsi (double a)
    {
    fprintf (stderr, "__fixunsdfsi() not implemented\n");
    exit (230);
    }

#endif
