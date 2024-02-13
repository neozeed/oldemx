/* _output.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define MAX_FRACT 20        /* 64 * log 2 */
#define MAX_MANT  309       /* extended format isn't used */
#define DEFAULT_PREC 6

#define PUTC(c) do { \
                   if (putc (c, stream) == EOF) \
                        return (-1); \
                   ++count; \
                   } while (0)

#ifdef USE_FLOATING_POINT
static void conv_real (char *dst, double x, int prec, int fixed, int force_dp,
                       int *prec_out, int *exp_out);
#endif


int _output (FILE *stream, const char *format, char *arg_ptr)
    {
    char just, sign, blank, hash, size, upper, number, integer, pad, cont, fix;
    char *s, *q, tmp[64], prefix[8], *pfx_ptr, *pfx_start, tbuf[40];
    int width, prec, count, *ptr, n, i, pn, zn, sn, tzn, neg;
#ifdef USE_FLOATING_POINT
    double dn;
    char dbuf[MAX_MANT+MAX_FRACT+10];
    int de;
#endif

    count = 0;
    while (*format != 0)
        if (*format != '%' || format[1] == '%')
            {
            PUTC (*format);
            ++format;
            }
        else
            {
            just = sign = blank = hash = upper = FALSE;
            width = 0; prec = -1; size = 0; tzn = 0; pad = ' ';
            cont = TRUE;
            while (cont)
                {
                ++format;
                switch (*format)
                    {
                    case '-': just = TRUE; break;
                    case '+': sign = TRUE; break;
                    case '0': pad = '0'; break;
                    case ' ': blank = TRUE; break;
                    case '#': hash = TRUE; break;
                    default: cont = FALSE; break;
                    }
                }
            if (*format == '*')
                {
                ++format;
                width = va_arg (arg_ptr, int);
                if (width < 0)
                    {
                    width = -width; just = TRUE;
                    }
                }
            else
                while (*format >= '0' && *format <= '9')
                    {
                    width = width * 10 + (*format - '0');
                    ++format;
                    }
            if (*format == '.')
                {
                pad = ' ';
                ++format;
                if (*format == '*')
                    {
                    ++format;
                    prec = va_arg (arg_ptr, int);
                    if (prec < 0) prec = -1;
                    }
                else
                    {
                    prec = 0;
                    while (*format >= '0' && *format <= '9')
                        {
                        prec = prec * 10 + (*format - '0');
                        ++format;
                        }
                    }
                }
            if (*format == 'h' || *format == 'l' || *format == 'L')
                size = *format++;
            s = NULL; number = TRUE; integer = TRUE;
            pfx_ptr = pfx_start = prefix+1;
            tbuf[0] = 0;
            switch (*format)
                {
                case 'n':
                    ptr = va_arg (arg_ptr, int *);
                    *ptr = count;
                    goto next;
                case 'c':
                    number = FALSE;
                    tmp[0] = (char)va_arg (arg_ptr, int);
                    s = tmp; sn = 1;
                    break;
                case 'u':
                    n = va_arg (arg_ptr, int);
                    if (size == 'h') n = (unsigned short)n;
                    s = ultoa (n, tmp, 10);
                    sn = strlen (s);
                    break;
                case 'd':
                case 'i':
                    n = va_arg (arg_ptr, int);
                    if (size == 'h') n = (short)n;
                    s = itoa (n, tmp, 10);
                    sn = strlen (s);
                    break;
                case 'p':
                case 'x':
                case 'X':
                    n = va_arg (arg_ptr, int);
                    if (size == 'h') n = (unsigned short)n;
                    s = itoa (n, tmp, 16);
                    sn = strlen (s);
                    if (*format == 'X')
                        strupr (tmp);
                    if (n != 0 && hash)
                        {
                        *pfx_ptr++ = '0';
                        *pfx_ptr++ = 'x';
                        }
                    break;
                case 'o':
                    n = va_arg (arg_ptr, int);
                    if (size == 'h') n = (unsigned short)n;
                    s = itoa (n, tmp, 8);
                    sn = strlen (s);
                    if (n != 0 && hash)
                        *pfx_ptr++ = '0';
                    break;
#ifdef USE_FLOATING_POINT
                case 'g':
                case 'G':
                case 'e':
                case 'E':
                case 'f':
                    if (prec == -1) prec = DEFAULT_PREC;
                    dn = va_arg (arg_ptr, double);
                    neg = (dn < 0.0);
                    if (neg) dn = -dn;
                    tzn = prec;
                    if (prec > MAX_FRACT) prec = MAX_FRACT;
                    switch (_fxam (dn))
                        {
                        case FX_P_NAN:      s = "#NAN"; break;
                        case FX_N_NAN:      s = "-#NAN"; break;
                        case FX_P_INFINITY: s = "#INF"; break;
                        case FX_N_INFINITY: s = "-#INF"; break;
                        case FX_P_EMPTY:    s = "#EMP"; break;
                        case FX_N_EMPTY:    s = "-#EMP"; break;
                        case FX_P_DENORMAL: s = "#DEN"; break;
                        case FX_N_DENORMAL: s = "-#DEN"; break;
                        default:            s = NULL; break;
                        }
                    if (s != NULL)
                        {
                        sn = strlen (s); prec = tzn = 0;
                        break;
                        }
                    switch (*format)
                        {
                        case 'f':
                            conv_real (dbuf, dn, prec, TRUE, hash, &i, &de);
                            tzn -= prec - i;
                            break;
                        case 'g':
                        case 'G':
                            if (dn == 0.0)
                                {
                                dbuf[1] = '0';
                                dbuf[2] = 0;
                                if (!hash) tzn = 0;
                                break;
                                }
                            conv_real (dbuf, dn, prec+1, FALSE, FALSE, &tzn, &de);
                            fix = !(de < -4 || de > prec);
                            if (fix)
                                {
                                conv_real (dbuf, dn, prec, TRUE, hash, &i, &de);
                                tzn -= prec - i;
                                }
                            if (!hash)
                                {
                                i = strlen (dbuf+1);
                                while (i > 1 && dbuf[i] == '0') --i;
                                if (i > 1 && dbuf[i] == '.') --i;
                                dbuf[i+1] = 0;
                                tzn = 0;
                                }
                            if (!fix) goto fmt_e;
                            break;
                        case 'e':
                        case 'E':
                            if (dn == 0.0)
                                {
                                s = dbuf + 1;
                                *s++ = '0';
                                if (prec != 0 || hash) *s++ = '.';
                                *s = 0; de = 0;
                                }
                            else
                                conv_real (dbuf, dn, prec+1, FALSE, FALSE, &tzn, &de);
fmt_e:
                            tbuf[0] = (*format >= 'A' && *format <= 'Z' ? 'E' : 'e');
                            tbuf[1] = (de < 0 ? '-' : '+');
                            if (de < 0) de = -de;
                            tbuf[2] = (char)((de / 100) % 10) + '0';
                            tbuf[3] = (char)((de / 10) % 10) + '0';
                            tbuf[4] = (char)(de % 10) + '0';
                            tbuf[5] = 0;
                            break;
                        }
                    if (neg)
                        {
                        dbuf[0] = '-';
                        s = dbuf;
                        }
                    else
                        s = dbuf + 1;
                    sn = strlen (s); prec = 0;
                    break;
#endif
                case 's':
                    number = FALSE;
                    s = va_arg (arg_ptr, char *);
                    if (s == NULL) s = "(null)";
                    sn = strlen (s);
                    if (prec > 0 && prec < sn)
                        sn = prec;
                    break;
                default:
                    if (size != 0)
                        --format;
                    PUTC (*format);
                    break;
                }
            if (s != NULL)
                {
                if (number && sn > 0 && *s != '-')
                    {
                    if (sign)
                        *--pfx_start = '+';
                    else if (blank)
                        *--pfx_start = ' ';
                    }
                zn = 0;
                if (number && integer && prec > 0)
                    {
                    zn = prec - sn;
                    if (sn > 0 && *s == '-') ++zn;
                    if (zn < 0) zn = 0;
                    }
                pn = pfx_ptr - pfx_start;
                if (tzn < 0) tzn = 0;
                n = pn + zn + sn + tzn + strlen (tbuf);
                if (n < width && !just)
                    for (i = n; i < width; ++i)
                        PUTC (pad);
                for (i = 0; i < pn; ++i)
                    {
                    PUTC (*pfx_start); ++pfx_start;
                    }
                for (i = 0; i < zn; ++i)
                    PUTC ('0');
                for (i = 0; i < sn; ++i)
                    {
                    PUTC (*s); ++s;
                    }
                for (i = 0; i < tzn; ++i)
                    PUTC ('0');
                for (i = 0; tbuf[i] != 0; ++i)
                    PUTC (tbuf[i]);
                if (n < width && just)
                    for (i = n; i < width; ++i)
                        PUTC (' ');
                }
next:
            ++format;
            }
    return (count);
    }


#ifdef USE_FLOATING_POINT

static void conv_real (char *dst, double x, int prec, int fixed, int force_dp,
                       int *prec_out, int *exp_out)
    {
    double df, dt, di;
    char tmp[MAX_MANT+MAX_FRACT+10], c, *start;
    int i, exp, leading_zero;

    start = dst++;
    df = modf (x, &di);
    i = 0; exp = -1; leading_zero = !fixed;
    while (di != 0.0)
        {
        dt = modf (di / 10.0, &di);
        tmp[i++] = (char)(dt * 10.0 + 0.125) + '0';
        ++exp; leading_zero = FALSE;
        }
    if (fixed)
        {
        if (i == 0) *dst++ = '0';
        while (i != 0)
            *dst++ = tmp[--i];
        if (prec > 0 || force_dp) *dst++ = '.';
        }
    else
        while (i != 0 && prec > 0)
            {
            *dst++ = tmp[--i];
            --prec;
            }
    while (df != 0.0 && prec > 0)
        {
        df = modf (df * 10.0, &dt);
        c = (char)dt + '0';
        if (c != '0' || !leading_zero)
            {
            *dst++ = c; leading_zero = FALSE;
            --prec;
            }
        else
            --exp;
        }
    *dst = 0;
    if (df != 0.0)
        {
        df = modf (df * 10.0, &dt);
        c = (char)dt + '0';
        if (c >= '5')
            {
            *start = '0';
            while (dst != start)
                {
                --dst;
                if (*dst == '.') continue;
                if (*dst != '9')
                    {
                    ++*dst; break;
                    }
                *dst = '0';
                }
            if (dst == start)
                (void)memmove (start+1, start, strlen (start)+1);
            }
        }
    if (!fixed)
        {
        (void)memmove (start+3, start+2, strlen (start+1));
        start[2] = '.';
        }
    *prec_out = prec;
    *exp_out = exp;
    }

#endif
