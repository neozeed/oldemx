/* sprintf.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

int sprintf (char *buffer, const char *format, ...)
    {
    va_list arg_ptr;
    struct _stdio trick;
    int result;

    va_start (arg_ptr, format);
    trick.buffer = buffer;
    trick.ptr = buffer;
    trick.rcount = 0;
    trick.wcount = INT_MAX;
    trick.handle = -1;
    trick.flags = _IOOPEN|_IOSTRING|_IOBUFUSER|_IOWRT;
    trick.buf_size = INT_MAX;
    result = _output (&trick, format, arg_ptr);
    (void)putc (0, &trick);
    va_end (arg_ptr);
    return (result);
    }
