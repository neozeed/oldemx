/* system.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <process.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int system (const char *name)
    {
    int argc, arga, i;
    char *tmp, *p, *q, *sh;
    const char *add = " /c ";
    char **argv;

    sh = getenv ("COMSPEC");
    if (sh == NULL)
        {
        errno = ENOENT;
        return (-1);
        }
    if (name == NULL)   /* Check for command interpreter */
        return (access (sh, 0) == 0);
    if (*name == 0)
        add = "";
    tmp = malloc (strlen (sh) + strlen (add) + strlen (name) + 1);
    if (tmp == NULL)
        {
        errno = ENOMEM;
        return (-1);
        }
    (void)strcpy (tmp, sh);
    (void)strcat (tmp, add);
    (void)strcat (tmp, name);
    argc = 0; arga = 0; argv = NULL;
    p = tmp;
    do  {
        q = strtok (p, " \t\n");
        ++argc;
        if (argc > arga)
            {
            arga += 20;
            argv = (char **)realloc (argv, arga * sizeof (char *));
            if (argv == NULL)
                {
                free (tmp);
                errno = ENOMEM;
                return (-1);
                }
            }
        argv[argc-1] = q;
        p = NULL;
        } while (q != NULL);
    i = spawnvp (P_WAIT, argv[0], (char const * const *)argv);
    free (tmp); free (argv);
    return (i);
    }
