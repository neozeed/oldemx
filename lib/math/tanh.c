/* tanh.c (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes */

#include <stdio.h>
#include <math.h>

double tanh (double x)
    {
    double t;

    t = exp (2.0 * x);
    return ((t-1.0)/(t+1.0));
    }
