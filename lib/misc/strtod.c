/* strtod.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

#ifdef USE_FLOATING_POINT

double strtod (const char *string, char **end_ptr)
    {
    double x, d;
    int exp;
    char neg, ok, eneg;

    neg = ok = FALSE; x = 0.0;
    while (isspace ((unsigned char)*string)) ++string;
    if (*string == '+')
        ++string;
    else if (*string == '-')
        {
        neg = TRUE; ++string;
        }
    while (isdigit ((unsigned char)*string))
        {
        x = x * 10.0 + (double)(*string - '0');
        ++string; ok = TRUE;
        }
    if (*string == '.')
        {
        ++string; d = 10.0;
        while (isdigit ((unsigned char)*string))
            {
            x += (double)(*string - '0') / d;
            d *= 10.0;
            ++string; ok = TRUE;
            }
        }
    if (!ok)
        {
        if (end_ptr != NULL) *end_ptr = (char *)string;
        return (0.0);
        }
    if (*string == 'e' || *string == 'E')
        {
        ++string; eneg = FALSE; exp = 0;
        if (*string == '+')
            ++string;
        else if (*string == '-')
            {
            eneg = TRUE; ++string;
            }
        if (!isdigit ((unsigned char)*string))
            {
            if (end_ptr != NULL) *end_ptr = (char *)string;
            return (0.0);
            }
        while (isdigit ((unsigned char)*string))
            {
            exp = exp * 10 + (*string - '0');
            ++string;
            }
        if (eneg) exp = -exp;
        while (exp > 0)
            {
            x *= 10.0;
            --exp;
            }
        while (exp < 0)
            {
            x /= 10.0;
            ++exp;
            }
        }
    if (end_ptr != NULL) *end_ptr = (char *)string;
    return (neg ? -x : x);
    }

#else

double strtod (const char *string, char **end_ptr)
    {
    fprintf (stderr, "strtod() not implemented\n");
    exit (230);
    }

#endif
