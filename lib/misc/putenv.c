/* putenv.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int putenv (const char *string)
    {
    char *s, **p;
    int len, env_size;

    if (string == NULL)
        {
        errno = EINVAL;
        return (-1);
        }
    s = strchr (string, '=');
    if (s == NULL)
        len = strlen (string);        /* Use complete string */
    else
        len = s - string;
    p = environ;
    env_size = 0;
    if (p != NULL)
        while (*p != NULL)
            {
            s = *p;
            if (strlen (s) >= len && memcmp (s, string, len) == 0 &&
                                     (s[len] == 0 || s[len] == '='))
                break;
            ++p; ++env_size;
            }
    if (p == NULL || *p == NULL)
        {
        if (environ == _org_environ)
            {
            environ = malloc ((env_size+2) * sizeof (char *));
            if (environ == NULL) return (-1);
            if (env_size != 0)
                (void)memcpy (environ, _org_environ, env_size * sizeof (char *));
            }
        else
            {
            environ = realloc (environ, (env_size+2) * sizeof (char *));
            if (environ == NULL) return (-1);
            }
        environ[env_size+0] = (char *)string;
        environ[env_size+1] = NULL;
        return (0);
        }
    else
        *p = (char *)string;
    return (-1);
    }
