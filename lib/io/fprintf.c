/* fprintf.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <stdarg.h>

int fprintf (FILE *stream, const char *format, ...)
    {
    va_list arg_ptr;
    int result;

    va_start (arg_ptr, format);
    _tmpbuf (stream);
    result = _output (stream, format, arg_ptr);
    _endbuf (stream);
    va_end (arg_ptr);
    return (result);
    }
