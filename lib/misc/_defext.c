/* _defext.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE  1

void _defext (char *dst, const char *ext)
    {
    int dot, sep;

    dot = FALSE; sep = TRUE;
    while (*dst != 0)
        switch (*dst++)
            {
            case '.':
                dot = TRUE;
                sep = FALSE;
                break;
            case ':':
            case '/':
            case '\\':
                dot = FALSE;
                sep = TRUE;
                break;
            default:
                sep = FALSE;
                break;
            }
    if (!dot && !sep)
        {
        *dst++ = '.';
        (void)strcpy (dst, ext);
        }
    }
