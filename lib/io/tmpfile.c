/* tmpfile.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */
/*                        Copyright (c) 1991      by Kolja Elsaesser */

#include <sys/emx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define IDX_LO 10000000
#define IDX_HI 99999999

static int _tmpidx = IDX_LO;

FILE *tmpfile (void)
    {
    char name[L_tmpnam], *p;
    FILE *f;

    if (tmpnam (name) == NULL)
        return (NULL);
    f = fopen (name, "w+b");
    if (f == NULL)
        return (NULL);
    f->tmpidx = _tmpidx;
    f->flags |= F_TMP;
    return (f);
    }


char *tmpnam (char *string)
    {
    char *p;
    int saved_errno, idx_start;
    static char buf[L_tmpnam];

    if (string == NULL) string = buf;
    (void)strcpy (string, P_tmpdir);
    p = strchr (string, 0);
    if (string[0] != 0 && p[-1] != '\\' && p[-1] != '/' && p[-1] != ':')
        *p++ = '/';
    saved_errno = errno;
    idx_start = _tmpidx;
    for (;;)
        {
        if (_tmpidx >= IDX_HI)
            _tmpidx = IDX_LO;
        else
            ++_tmpidx;
        if (_tmpidx == idx_start)
            {
            errno = EINVAL;
            return (NULL);
            }
        (void)itoa (_tmpidx, p, 10);
        (void)strcat (p, ".tmp");
        errno = 0;
        if (access (string, 0) != 0 && errno == ENOENT)
            break;
        }
    errno = saved_errno;
    return (string);
    }


char *tempnam (const char *dir, const char *prefix)
    {
    const char *tmpdir;
    char *tmpname, *p;
    int attr, saved_errno, idx_start;

    saved_errno = errno;
    if (strlen (dir) >= sizeof (tmpdir))
        {
        errno = EINVAL;
        return (NULL);
        }
    if (strlen (prefix) > 5)
        {
        errno = EINVAL;
        return (NULL);
        }
    tmpdir = NULL;
    p = getenv ("TMP");
    if (tmpdir == NULL && p != NULL)
        {
        attr = _chmod (p, 0, 0);
        if (attr >= 0 && (attr & _A_SUBDIR))
            tmpdir = p;
        }
    if (tmpdir == NULL && dir != NULL)
        {
        attr = _chmod (dir, 0, 0);
        if (attr >= 0 && (attr & _A_SUBDIR))
            tmpdir = dir;
        }
    if (tmpdir == NULL)
        tmpdir = P_tmpdir;
    tmpname = malloc (strlen (tmpdir) + 1 + L_tmpnam);
    if (tmpname == NULL)
        {
        errno = ENOMEM;
        return (NULL);
        }
    (void)strcpy (tmpname, tmpdir);
    p = strchr (tmpname, 0);
    if (tmpname[0] != 0 && p[-1] != '\\' && p[-1] != '/' && p[-1] != ':')
        *p++ = '/';
    idx_start = _tmpidx;
    for (;;)
        {
        if (_tmpidx == IDX_HI)
            _tmpidx = IDX_LO;
        else
            ++_tmpidx;
        if (_tmpidx == idx_start)
            {
            free (tmpname);
            errno = EINVAL;
            return (NULL);
            }
        (void)itoa (_tmpidx, p, 10);
        (void)strcat (p, ".tmp");
        (void)memmove (p, prefix, strlen (prefix));
        errno = 0;
        if (access (tmpname, 0) != 0 && errno == ENOENT)
            break;
        }
    errno = saved_errno;
    return (tmpname);
    }
