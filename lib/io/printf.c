/* printf.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <stdarg.h>

int printf (const char *format, ...)
    {
    va_list arg_ptr;
    int result;

    va_start (arg_ptr, format);
    _tmpbuf (stdout);
    result = _output (stdout, format, arg_ptr);
    _endbuf (stdout);
    va_end (arg_ptr);
    return (result);
    }
