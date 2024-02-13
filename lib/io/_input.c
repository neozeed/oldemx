/* _input.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

/* %[...] not yet implemented */

#define WHITE(x) ((x) == ' ' || (x) == '\t' || (x) == '\n')

#define NEXT(x) do { x = getc (stream); \
                     if (x == EOF) return (count == 0 ? EOF : count); \
                     ++chars; \
                   } while (0)
#define UNGETC(x) do { ungetc (x, stream); --chars; } while (0)


int _input (FILE *stream, const char *format, char *arg_ptr)
    {
    int count, chars, c, width, radix, d, i;
    int *int_ptr;
    short *short_ptr;
    char *char_ptr;
    unsigned char f;
    char neg, assign, ok, size;
    unsigned long n;
    char map[256], end;
#ifdef USE_FLOATING_POINT
    double dx, dd, *dbl_ptr;
    float *flt_ptr;
    int exp;
    char eneg;
#endif

    count = 0; chars = 0;
    while ((f = *format) != 0)
        {
        if (WHITE (f))
            {
            do  {
                ++format; f = *format;
                } while (WHITE (f));
            do  {
                c = getc (stream);
                if (c == EOF)
                    {
                    if (f == 0 || count != 0)
                        return (count);
                    else
                        return (EOF);
                    }
                else
                    ++chars;
                } while (WHITE (c));
            UNGETC (c);
            }
        else if (f != '%')
            {
            NEXT (c);
            if (c != f)
                return (count);
            ++format;
            }
        else
            {
            assign = TRUE; width = INT_MAX;
            ++format;
            if (*format == '*')
                {
                assign = FALSE;
                ++format;
                }
            if (isdigit (*format))
                {
                width = 0;
                while (isdigit (*format))
                    width = width * 10 + (*format++ - '0');
                if (width == 0) width = INT_MAX;
                }
            size = 0;
            if (*format == 'h' || *format == 'l')
                size = *format++;
            f = *format;
            switch (f)
                {
                case 'c':
                    NEXT (c);
                    if (assign)
                        {
                        char_ptr = va_arg (arg_ptr, char *);
                        *char_ptr = (char)c;
                        ++count;
                        }
                    break;
                case '[':
                    memset (map, 0, 256);
                    end = 0;
                    ++format;
                    if (*format == '^')
                        {
                        ++format; end = 1;
                        }
                    i = 0;
                    for (;;)
                        {
                        f = (unsigned char)*format;
                        switch (f)
                            {
                            case 0:
                                --format;       /* avoid skipping past 0 */
                                goto string;
                            case ']':
                                if (i > 0)
                                    goto string;
                                /* no break */
                            default:
                                if (format[1] == '-' && format[2] != 0 &&
                                        f < (unsigned char)format[2])
                                    {
                                    memset (map+f, 1,
                                            (unsigned char)format[2] - f);
                                    format += 2;
                                    }
                                else
                                    map[f] = 1;
                                break;
                            }
                        ++format; ++i;
                        }

                case 's':
                    memset (map, 0, 256);
                    map[' '] = 1;
                    map['\n'] = 1;
                    map['\t'] = 1;
                    end = 1;
string:
                    if (assign)
                        char_ptr = va_arg (arg_ptr, char *);
                    do  {
                        NEXT (c);
                        } while (WHITE (c));
                    for (;;)
                        {
                        if (width <= 0)
                            break;
                        --width;
                        if (assign)
                            *char_ptr++ = (char)c;
                        c = getc (stream);
                        if (c == EOF)
                            break;
                        else
                            ++chars;
                        if (map[(unsigned char)c] == end)
                            break;
                        }
                    if (assign)
                        {
                        *char_ptr = 0;
                        ++count;
                        }
                    if (c == EOF)
                        return (count);
                    else
                        UNGETC (c);
                    break;
#ifdef USE_FLOATING_POINT
                case 'f':
                case 'e':
                case 'E':
                case 'g':
                case 'G':
                    neg = ok = FALSE; dx = 0.0;
                    do  {
                        NEXT (c);
                        } while (WHITE (c));
                    if (c == '+')
                        NEXT (c);
                    else if (c == '-')
                        {
                        neg = TRUE; NEXT (c);
                        }
                    while (isdigit (c))
                        {
                        dx = dx * 10.0 + (double)(c - '0');
                        ok = TRUE;
                        c = getc (stream);
                        if (c == EOF)
                            break;
                        else
                            ++chars;
                        }
                    if (c == '.')
                        {
                        dd = 10.0; NEXT (c);
                        while (isdigit (c))
                            {
                            dx += (double)(c - '0') / dd;
                            dd *= 10.0;
                            ok = TRUE;
                            c = getc (stream);
                            if (c == EOF)
                                break;
                            else
                                ++chars;
                            }
                        }
                    if (!ok) return (count);
                    if (c == 'e' || c == 'E')
                        {
                        eneg = FALSE; exp = 0; NEXT (c);
                        if (c == '+')
                            NEXT (c);
                        else if (c == '-')
                            {
                            eneg = TRUE; NEXT (c);
                            }
                        if (!isdigit (c))
                            {
                            UNGETC (c);
                            return (count);
                            }
                        while (isdigit (c))
                            {
                            exp = exp * 10 + (c - '0');
                            c = getc (stream);
                            if (c == EOF)
                                break;
                            else
                                ++chars;
                            }
                        if (eneg) exp = -exp;
                        while (exp > 0)
                            {
                            dx *= 10.0;
                            --exp;
                            }
                        while (exp < 0)
                            {
                            dx /= 10.0;
                            ++exp;
                            }
                        }
                    if (assign)
                        {
                        if (neg) dx = -dx;
                        if (size == 'l')
                            {
                            dbl_ptr = va_arg (arg_ptr, double *);
                            *dbl_ptr = dx;
                            }
                        else
                            {
                            flt_ptr = va_arg (arg_ptr, float *);
                            *flt_ptr = (float)dx;
                            }
                        ++count;
                        }
                    if (c == EOF)
                        return (count);
                    else
                        UNGETC (c);
                    break;
#endif
                case 'i':
                    neg = FALSE; radix = 10;
                    do  {
                        NEXT (c);
                        } while (WHITE (c));
                    if (c != '0')
                        goto scan_complete_number;
                    NEXT (c);
                    if (c == 'x' || c == 'X')
                        {
                        NEXT (c); radix = 16;
                        }
                    else if (c >= '0' && c <= '7')
                        radix = 8;
                    goto scan_unsigned_number;
                case 'd':
                case 'u':
                case 'o':
                case 'x':
                    do  {
                        NEXT (c);
                        } while (WHITE (c));
                    switch (f)
                        {
                        case 'o': radix = 8; break;
                        case 'x': radix = 16; break;
                        default: radix = 10; break;
                        }
scan_complete_number:
                    neg = FALSE;
                    if (c == '+')
                        NEXT (c);
                    else if (c == '-' && radix == 10)
                        {
                        neg = TRUE;
                        NEXT (c);
                        }
scan_unsigned_number:
                    n = 0; ok = FALSE;
                    for (;;)
                        {
                        if (isdigit (c))
                            d = c - '0';
                        else if (isupper (c))
                            d = c - 'A' + 10;
                        else if (islower (c))
                            d = c - 'a' + 10;
                        else
                            break;
                        if (d < 0 || d >= radix)
                            break;
                        ok = TRUE;
                        n = n * radix + d;
                        c = getc (stream);
                        if (c == EOF)
                            break;
                        else
                            ++chars;
                        }
                    if (!ok)
                        return (count);
                    if (assign)
                        {
                        if (neg) n = -n;
                        if (size == 'h')
                            {
                            short_ptr = va_arg (arg_ptr, short *);
                            *short_ptr = (short)n;
                            }
                        else
                            {
                            int_ptr = va_arg (arg_ptr, int *);
                            *int_ptr = (int)n;
                            }
                        ++count;
                        }
                    if (c == EOF)
                        return (count);
                    else
                        UNGETC (c);
                    break;
                case 'n':
                    if (assign)
                        {
                        int_ptr = va_arg (arg_ptr, int *);
                        *int_ptr = chars;
                        ++count;
                        }
                    break;
                default:
                    if (f == 0)                 /* % at end of string */
                        return (count);
                    NEXT (c);
                    if (c != f)
                        return (count);
                    break;
                }
            ++format;
            }
        }
    return (count);
    }
