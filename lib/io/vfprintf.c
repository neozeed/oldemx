/* vfprintf.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>

int vfprintf (FILE *stream, const char *format, va_list arg_ptr)
    {
    int result;

    _tmpbuf (stream);
    result = _output (stream, format, arg_ptr);
    _endbuf (stream);
    return (result);
    }
