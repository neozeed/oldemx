/* atof.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double atof (const char *s)
    {
    return (strtod (s, NULL));
    }
