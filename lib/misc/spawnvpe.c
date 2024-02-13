/* spawnvpe.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <process.h>

int spawnvpe (int mode, const char *name, const char * const *argv, const char * const *envp)
    {
    char exe[512];
    char path[512];

    (void)strcpy (exe, name);
    _defext (exe, "exe");
    if (_path (path, exe) != 0)
        return (-1);
    return (spawnve (mode, path, argv, envp));
    }
