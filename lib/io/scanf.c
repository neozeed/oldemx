/* scanf.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <stdarg.h>

int scanf (const char *format, ...)
    {
    va_list arg_ptr;

    va_start (arg_ptr, format);
    return (_input (stdin, format, arg_ptr));
    }
