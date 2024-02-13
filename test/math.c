/* math.c */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (void);

int main (void)
    {
    double x;

    if (!(_emx_env & 0x20))
        {
        (void)printf ("This program requires a coprocessor.\n");
        return (1);
        }
    while (scanf ("%lf", &x) == 1)
        {
        (void)printf ("x=%g, floor(x)=%g, ceil(x)=%g\n", x, floor (x), ceil (x));
        (void)printf ("fabs(x)=%g, sqrt(x)=%g\n", fabs (x), sqrt (x));
        (void)printf ("exp(x)=%g, log(x)=%g, log10(x)=%g\n", exp (x), log (x), log10 (x));
        (void)printf ("sinh(x)=%g, cosh(x)=%g, tanh(x)=%g\n", sinh (x), cosh (x), tanh (x));
        (void)printf ("sin(x)=%g, cos(x)=%g, tan(x)=%g\n", sin (x), cos (x), tan (x));
        (void)printf ("atan(x)=%g, asin(x)=%g, acos(x)=%g\n", atan (x), asin (x), acos (x));
        (void)printf ("atan2(x,1)=%g\n", atan2 (x, 1));
        (void)printf ("ldexp(x,0)=%g, ldexp(x,-2)=%g, ldexp(x,3)=%g\n", ldexp (x, 0), ldexp (x, -2), ldexp (x, 3));
        (void)printf ("pow(x,1.8)=%g pow(1.8,x)=%g\n", pow (x, 1.8), pow (1.8, x));
        (void)printf ("pow(x,3.8)=%g pow(3.8,x)=%g\n", pow (x, 3.8), pow (3.8, x));
        (void)printf ("pow(-2.0,x)=%g\n", pow (-2.0, x));
        }
    return (0);
    }
