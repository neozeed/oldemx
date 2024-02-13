/* _abspath.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>
#include <string.h>
#include <alloca.h>
#include <errno.h>
#include <sys/param.h>

#define IS_PATH_DELIM(c) ((c)=='\\' || (c)=='/')

int _abspath (char *dst, const char *src, int size)
    {
    char drive, dir[MAXPATHLEN+1], src_drive, *s, *p;
    int i, j, rel, server;

    s = alloca (strlen (src) + 1);
    (void)strcpy (s, src);
    src_drive = _fngetdrive (s);
    if (src_drive == 0)
	drive = _getdrive ();
    else
	{
	drive = src_drive;
	s += 2;
	}
    dir[0] = 0; rel = FALSE; server = FALSE;
    if (IS_PATH_DELIM (*s))
	{
	++s;
	if (IS_PATH_DELIM (*s))
	    {
	    ++s; server = TRUE;
	    }
	}
    else if (__getcwd (dir, drive) == 0)
	{
	for (p = dir; *p != 0; ++p)
	    if (*p == '\\')
		*p = '/';
	}
    else
	{
	dir[0] = 0;
	rel = TRUE;
	}
    while (*s != 0)
	{
	if (s[0] == '.' && (IS_PATH_DELIM (s[1]) || s[1] == 0))
	    {
	    ++s;
	    if (*s != 0)
		++s;
	    }
	else if (s[0] == '.' && s[1] == '.' && (IS_PATH_DELIM (s[2]) || 
						s[2] == 0))
	    {
	    s += 2;
	    if (*s != 0)
		++s;
	    i = strlen (dir);
	    if (i == 0)
		(void)strcpy (dir, "..");
	    else
		{
		--i;
		while (i > 0 && dir[i] != '/')
		    --i;
		dir[i] = 0;
		}
	    }
	else
	    {
	    i = strlen (dir);
	    if (i < sizeof (dir) - 1)
		dir[i++] = '/';
	    while (*s != 0 && !IS_PATH_DELIM (*s))
		{
		if (i < sizeof (dir) - 1)
		    dir[i++] = *s;
		++s;
		}
	    dir[i] = 0;
	    if (*s != 0)
		++s;
	    }
	}
    i = 0;
    if (i+1 < size && (src_drive != 0 || !server))
	{
	dst[i++] = drive;
	dst[i++] = ':';
	}
    if (i < size && server && src_drive == 0)
	dst[i++] = '/';
    if (i < size && !rel && dir[0] != '/')
	dst[i++] = '/';
    j = 0;
    if (rel && dir[j] == '/')
	++j;
    while (i < size && dir[j] != 0)
	dst[i++] = dir[j++];
    if (i >= size)
	{
	dir[size-1] = 0;
	errno = ERANGE;
	return (-1);
	}
    dst[i] = 0;
    return (0);
    }
