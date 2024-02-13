/* spawnve.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <errno.h>

int spawnve (int mode, const char *name, const char * const *argv,
             const char * const *envp)
    {
    struct _new_proc np;
    int i, size, n;
    const char * const *p;
    char *d;
    char exe[512];

    np.mode = mode;
    if (envp == NULL) envp = (const char * const *)environ;
    (void)strcpy (exe, name);
    _defext (exe, "exe");
    np.fname_off = (unsigned long)exe;
    size = 1; n = 0;
    for (p = envp; *p != NULL; ++p)
        {
        ++n; size += 1 + strlen (*p);
        }
    d = alloca (size);
    np.env_count = n; np.env_size = size;
    np.env_off = (unsigned long)d;
    for (p = envp; *p != NULL; ++p)
        {
        i = strlen (*p);
        (void)memcpy (d, *p, i+1);
        d += i+1;
        }
    *d = 0;
    size = 0; n = 0;
    for (p = argv; *p != NULL; ++p)
        {
        ++n; size += 2 + strlen (*p);
        }
    d = alloca (size);
    np.arg_count = n; np.arg_size = size;
    np.arg_off = (unsigned long)d;
    for (p = argv; *p != NULL; ++p)
        {
        i = strlen (*p);
        *d++ = (char)(_ARG_DQUOTE|_ARG_NONZERO);
        (void)memcpy (d, *p, i+1);
        d += i+1;
        }
    i = __spawnve (&np);
    return (i);
    }
