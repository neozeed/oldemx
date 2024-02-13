/* itoa.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdlib.h>

char *itoa (int value, char *string, int radix)
    {
    char *dst;
    char digits[32];
    unsigned x;
    int i, n;
  
    dst = string;
    if (radix < 2 || radix > 36)
        {
        *dst = 0;
        return (string);
        }
    if (radix == 10 && value < 0)
        {
        *dst++ = '-';
        x = -value;
        }
    else
        x = value;
    i = 0;
    do
        {
        n = x % (unsigned)radix;
        digits[i++] = (n < 10 ? (char)n+'0' : (char)n-10+'a');
        x /= (unsigned)radix;
        } while (x != 0);
    while (i > 0)
        *dst++ = digits[--i];
    *dst = 0;
    return (string);
    }
