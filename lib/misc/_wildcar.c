/* _wildcar.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PUT(x) do { \
    if (new_argc >= new_alloc) \
        { \
        new_alloc += 20; \
        new_argv = (char **)realloc (new_argv, new_alloc * sizeof (char *)); \
        if (new_argv == NULL) \
            goto out_of_memory; \
        } \
    new_argv[new_argc++] = x; \
    } while (0)



void _wildcard (int *argcp, char ***argvp)
    {
    int i, old_argc, new_argc, new_alloc;
    char **old_argv, **new_argv;
    char line[256], *p, *q;
    struct _find find;

    old_argc = *argcp; old_argv = *argvp;
    for (i = 1; i < old_argc; ++i)
        if (old_argv[i] != NULL &&
                 !(old_argv[i][-1] & (_ARG_DQUOTE|_ARG_RESPONSE)) &&
                 strpbrk (old_argv[i], "?*") != NULL)
            break;
    if (i >= old_argc)
        return;                 /* do nothing */
    new_argv = NULL; new_alloc = 0; new_argc = 0;
    for (i = 0; i < old_argc; ++i)
        {
        if (i == 0 || old_argv[i] == NULL
                   || (old_argv[i][-1] & (_ARG_DQUOTE|_ARG_RESPONSE))
                   || strpbrk (old_argv[i], "?*") == NULL
                   || _findfirst (old_argv[i], 0, &find) != 0)
            PUT (old_argv[i]);
        else
            {
            line[0] = _ARG_NONZERO|_ARG_WILDCARD;
            (void)strcpy (line+1, old_argv[i]);
            p = q = line + 1;
            while (*q != 0)
                {
                if (*q == ':' || *q == '\\' || *q == '/')
                    p = q + 1;
                ++q;
                }
            do  {
                (void)strcpy (p, find.name);
                (void)strlwr (line+1);
                q = strdup (line);
                PUT (q+1);
                } while (_findnext (&find) == 0);
            }
        }
    PUT (NULL); --new_argc;
    *argcp = new_argc; *argvp = new_argv;
    return;

out_of_memory:
    (void)fputs ("Out of memory while expanding wildcards\n", stderr);
    exit (255);
    }
