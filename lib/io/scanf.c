/* scanf.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <stdarg.h>

int scanf (const char *format, ...)
    {
    va_list arg_ptr;
    int result;

    va_start (arg_ptr, format);
    result = _input (stdin, format, arg_ptr);
    va_end (arg_ptr);
    return (result);
    }
