/* cosh.c (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes */

#include <stdio.h>
#include <math.h>

double cosh (double x)
    {
    return (0.5 * (exp (x) + exp (-x)));
    }
