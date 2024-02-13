/* vprintf.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>

int vprintf (const char *format, va_list arg_ptr)
    {
    int result;

    _tmpbuf (stdout);
    result = _output (stdout, format, arg_ptr);
    _endbuf (stdout);
    return (result);
    }
