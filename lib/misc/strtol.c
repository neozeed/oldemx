/* strtol.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <errno.h>
#include <stdlib.h>
#include <limits.h>

/* bug: -2147483648 overflows */

long strtol (const char *string, char **end_ptr, int radix)
    {
    char neg, c, ok;
    long result, max1, max2;

    while (*string == ' ' || *string == '\t')
        ++string;
    neg = 0; result = 0;
    if (*string == '-')
        {
        ++string; neg=1;
        }
    else if (*string == '+')
        ++string;
    if (radix == 0)
        {
        radix = 10;
        if (*string == '0')
            {
            ++string;
            if (*string == 'x' || *string == 'X')
                {
                radix = 16; ++string;
                }
            else
                radix = 8;
            }
        }
    else if (radix < 2 || radix > 36)
        goto error;
    ok = 0; max1 = LONG_MAX / radix; max2 = LONG_MAX - max1 * radix;
    for (;;)
        {
        c = *string;
        if (c >= '0' && c <= '9')
            c = c - '0';
        else if (c >= 'A' && c <= 'Z')
            c = c - 'A' + 10;
        else if (c >= 'a' && c <= 'z')
            c = c - 'a' + 10;
        else
            break;
        if (c >= radix)
            break;
        if (result >= max1)
            {
            if (result > max1 || (long)c > max2)
                goto overflow;
            }
        result = result * radix + (long)c;
        ++string; ok = 1;
        }
    if (ok)
        {
        if (neg) result = -result;
        goto done;
        }
error:
    errno = EINVAL;
    result = 0;
    goto done;

overflow:
    errno = ERANGE;
    result = (neg ? LONG_MIN : LONG_MAX);
done:
    if (end_ptr != NULL)
        *end_ptr = (char *)string;
    return (result);
    }
