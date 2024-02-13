/* fputchar.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdio.h>

int fputchar (int c)
    {
    return (putchar (c));
    }
