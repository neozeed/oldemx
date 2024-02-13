/* ultoa.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdlib.h>

char *ultoa (unsigned long value, char *string, int radix)
    {
    char *dst;
    char digits[32];
    int i, n;
  
    dst = string;
    if (radix < 2 || radix > 36)
        {
        *dst = 0;
        return (string);
        }
    i = 0;
    do
        {
        n = value % (unsigned long)radix;
        digits[i++] = (n < 10 ? (char)n+'0' : (char)n-10+'a');
        value /= (unsigned long)radix;
        } while (value != 0);
    while (i > 0)
        *dst++ = digits[--i];
    *dst = 0;
    return (string);
    }
