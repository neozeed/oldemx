/* math.h (emx/gcc) */

double acos (double x);
double asin (double x);
double atan (double x);
double atan2 (double y, double x);
double atof (const char *string);
double ceil (double x);
double cos (double x);
double cosh (double x);
double exp (double x);
double fabs (double x);
double floor (double x);
double fmod (double x, double y);
double frexp (double x, int *exp_ptr);
double ldexp (double x, int exp);
double log (double x);
double log10 (double x);
double modf (double x, double *int_ptr);
double pow (double x, double y);
double sin (double x);
double sinh (double x);
double sqrt (double x);
double tan (double x);
double tanh (double x);

#if !defined (__ABS)                                   /* see also stdlib.h */
#define __ABS
static __inline__ int abs (int n) { return (n < 0 ? -n : n); }
static __inline__ long labs (long n) { return (n < 0 ? -n : n); }
#endif
