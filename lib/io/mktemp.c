/* mktemp.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <io.h>
#include <string.h>
#include <process.h>
#include <errno.h>

char *mktemp (char *template)
    {
    int pid, n, saved_errno;
    char *s;

    pid = getpid ();
    s = strchr (template, 0);
    n = 0;
    while (s != template && s[-1] == 'X')
        {
        --s; ++n;
        *s = (char)(pid % 10) + '0';
        pid /= 10;
        }
    if (n < 2)
        return (NULL);
    *s = 'a'; saved_errno = errno;
    for (;;)
        {
        errno = 0;
        if (access (template, 0) != 0 && errno == ENOENT)
            {
            errno = saved_errno;
            return (template);
            }
        if (*s == 'z')
            {
            errno = saved_errno;
            return (NULL);
            }
        ++*s;
        }
    }
