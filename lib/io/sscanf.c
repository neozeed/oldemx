/* sscanf.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

int sscanf (const char *buffer, const char *format, ...)
    {
    va_list arg_ptr;
    struct _stdio trick;
    int result;

    va_start (arg_ptr, format);
    trick.buffer = (char *)buffer;              /* const -> non-const */
    trick.ptr = (char *)buffer;                 /* const -> non-const */
    trick.rcount = strlen (buffer);
    trick.wcount = 0;
    trick.handle = -1;
    trick.flags = _IOOPEN|_IOSTRING|_IOBUFUSER|_IOREAD;
    trick.buf_size = INT_MAX;
    result = _input (&trick, format, arg_ptr);
    va_end (arg_ptr);
    return (result);
    }
