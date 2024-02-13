/* spawnle.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <stddef.h>
#include <process.h>
#include <stdarg.h>

int spawnle (int mode, const char *name, const char *arg0, ...)
    {
    va_list arg_ptr;
    const char * const *env_ptr;
    int result;

    va_start (arg_ptr, name);
    while (va_arg (arg_ptr, char *) != NULL)
        /* do nothing */;
    env_ptr = va_arg (arg_ptr, const char * const *);
    va_end (arg_ptr);
    va_start (arg_ptr, name);
    result = spawnve (mode, name, (const char * const *)arg_ptr, env_ptr);
    va_end (arg_ptr);
    return (result);
    }
