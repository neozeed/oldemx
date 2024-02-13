/* popen.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <io.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

static void restore (int org_handle, int org_private, int handle)
    {
    int saved_errno;

    saved_errno = errno;
    (void)close (handle);
    (void)dup (org_handle);
    (void)close (org_handle);
    (void)fcntl (handle, F_SETFD, org_private);
    errno = saved_errno;
    }

static FILE *make_pipe (int pipe_local, int pipe_remote, int handle,
                        const char *command, const char *mode)
    {
    int i, argc, arga, org_handle, org_private;
    FILE *f;
    const char *sh, *add = " /c ";
    char *tmp, *p, *q, **argv;

    org_private = fcntl (handle, F_GETFD, 0);
    if (org_private == -1)
        return (NULL);
    org_handle = dup (handle);
    if (org_handle == -1)
        return (NULL);
    if (close (handle) == -1)
        return (NULL);
    i = dup (pipe_remote);
    if (i == -1)
        return (NULL);
    if (i != handle)
        {
        restore (org_handle, org_private, handle);
        errno = EBADF;
        return (NULL);
        }
    if (close (pipe_remote) == -1)
        {
        restore (org_handle, org_private, handle);
        return (NULL);
        }
    f = fdopen (pipe_local, mode);
    if (f == NULL)
        {
        restore (org_handle, org_private, handle);
        return (NULL);
        }
    (void)fcntl (org_handle, F_SETFD, 1);
    sh = getenv ("COMSPEC");
    if (sh == NULL)
        {
        (void)fclose (f);
        restore (org_handle, org_private, handle);
        errno = ENOENT;
        return (NULL);
        }
    tmp = malloc (strlen (sh) + strlen (add) + strlen (command) + 1);
    if (tmp == NULL)
        {
        errno = ENOMEM;
        return (NULL);
        }
    (void)strcpy (tmp, sh);
    (void)strcat (tmp, add);
    (void)strcat (tmp, command);
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
                (void)fclose (f);
                restore (org_handle, org_private, handle);
                free (tmp);
                errno = ENOMEM;
                return (NULL);
                }
            }
        argv[argc-1] = q;
        p = NULL;
        } while (q != NULL);
    i = spawnvp (P_NOWAIT, argv[0], (char const * const *)argv);
    free (tmp); free (argv);
    if (i == -1)
        {
        (void)fclose (f);
        f = NULL;
        }
    f->pid = i;
    restore (org_handle, org_private, handle);
    return (f);
    }


FILE *popen (const char *command, const char *mode)
    {
    int ph[2];

    if (mode[0] != 'r' && mode[0] != 'w')
        {
        errno = EINVAL;
        return (NULL);
        }
    if (pipe (ph) == -1)
        return (NULL);
    if (fcntl (ph[0], F_SETFD, 1) == -1)
        return (NULL);
    if (fcntl (ph[1], F_SETFD, 1) == -1)
        return (NULL);
    if (mode[0] == 'r')
        return (make_pipe (ph[0], ph[1], STDOUT_FILENO, command, mode));
    else
        return (make_pipe (ph[1], ph[0], STDIN_FILENO, command, mode));
    }
