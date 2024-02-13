/* _fullpat.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alloca.h>
#include <errno.h>
#include <sys/param.h>

#define IS_PATH_DELIM(c) ((c)=='\\' || (c)=='/')

int _fullpath (char *dst, const char *src, int size)
    {
    char drive, cwd1[MAXPATHLEN+1], cwd2[MAXPATHLEN+1];
    char *temp, c;
    int i, j, k, add_file;

    drive = _fngetdrive (src);
    if (drive == 0)
        drive = _getdrive ();
    else
        src += 2;
    i = strlen (src);
    temp = (char *)alloca (i+2+1);
    temp[0] = drive; temp[1] = ':';
    (void)strcpy (temp+2, src);
    cwd1[0] = cwd2[0] = drive;
    cwd1[1] = cwd2[1] = ':';
    cwd1[2] = cwd2[2] = '/';
    if (__getcwd (cwd1+3, drive) != 0)
        goto failure;
    add_file = 0; k = 0;
    if (chdir (temp) != 0)
        {
        k = i+2-1;
        while (k > 1 && !IS_PATH_DELIM (temp[k]))
            --k;
        if (k == 2)
            {
            ++k;
            c = temp[k]; temp[k] = 0;
            if (chdir (temp) != 0)
                goto failure;
            temp[k] = c;
            }
        else if (k > 2)
            {
            temp[k] = 0;
            if (chdir (temp) != 0)
                goto failure;
            ++k;
            }
        else
            ++k;
        add_file = 1;
        }
    j = __getcwd (cwd2+3, drive);
    if (chdir (cwd1) != 0 || j != 0)
        goto failure;
    if (strlen (cwd2)+1 > size)
        {
        errno = ERANGE;
        goto failure;
        }
    (void)strcpy (dst, cwd2);
    if (add_file && temp[k] != 0)
        {
        j = strlen (dst);
        if (j+1+strlen (temp+k)+1 > size)
            {
            errno = ERANGE;
            goto failure;
            }
        if (!IS_PATH_DELIM (dst[j-1]))
            dst[j++] = '/';
        (void)strcpy (dst+j, temp+k);
        }
    for (temp = dst; *temp != 0; ++temp)
        if (*temp == '\\') *temp = '/';
    return (0);

failure:
    dst[0] = 0;
    return (-1);
    }
