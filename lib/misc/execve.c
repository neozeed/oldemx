/* execve.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <process.h>

int execve (const char *name, const char * const *argv,
            const char * const *envp)
    {
    return (spawnve (P_OVERLAY, name, argv, envp));
    }
