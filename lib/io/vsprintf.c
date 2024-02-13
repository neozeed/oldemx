/* vsprintf.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <limits.h>

int vsprintf (char *buffer, const char *format, va_list arg_ptr)
    {
    struct _stdio trick;
    int result;

    trick.buffer = buffer;
    trick.ptr = buffer;
    trick.rcount = 0;
    trick.wcount = INT_MAX;
    trick.handle = -1;
    trick.flags = F_STRING|F_USER_BUF|_IOWRT;
    trick.buf_size = INT_MAX;
    result = _output (&trick, format, arg_ptr);
    putc (0, &trick);
    return (result);
    }
