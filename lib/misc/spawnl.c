/* spawnl.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <stddef.h>
#include <process.h>
#include <stdarg.h>

int spawnl (int mode, const char *name, const char *arg0, ...)
    {
    va_list arg_ptr;
    int result;

    va_start (arg_ptr, name);
    result = spawnv (mode, name, (const char * const *)arg_ptr);
    va_end (arg_ptr);
    return (result);
    }
