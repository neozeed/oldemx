/* dirent.c (emx/gcc) */

#include <sys/emx.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <io.h>
#include <string.h>
#include <errno.h>

static void free_dircontents (struct _dircontents *dp);
static char *getdirent (char *dir);


static struct _find find;

DIR *opendir (const char *name)
    {
    struct stat statb;
    DIR *dirp;
    char c;
    char *s;
    struct _dircontents *dp;
    char nbuf[MAXPATHLEN+1];
    int len;
  
    (void)strcpy (nbuf, name);
    len = strlen (nbuf);
    s = nbuf + len;
    if (len > 0)
        {
        c = nbuf[len-1];
        if (c == '\\' || c == '/' || c == ':')
            {
            nbuf[len++] = '.';      /* s now points to '.' */
            nbuf[len] = 0;
            }
        }
    if (stat (nbuf, &statb) < 0 || (statb.st_mode & S_IFMT) != S_IFDIR)
        {
        errno = ENOENT;
        return (NULL);
        }
    dirp = malloc (sizeof (DIR));
    if (dirp == NULL)
        {
        errno = ENOMEM;
        return (NULL);
        }
    if (*s == 0)
        *s++ = '\\';
    (void)strcpy (s, "*.*");
    dirp->dd_loc = 0;
    dirp->dd_contents = NULL;
    dirp->dd_cp = NULL;
    s = getdirent (nbuf);
    if (s == NULL)
        {
        errno = ENOMEM;
        return (dirp);
        }
    do  {
        dp = malloc (sizeof (struct _dircontents));
        if (dp == NULL)
            {
            free_dircontents (dirp->dd_contents);
            errno = ENOMEM;
            return (NULL);
            }
        dp->_d_entry = malloc (strlen (s) + 1);
        if (dp->_d_entry == NULL)
            {
            free (dp);
            free_dircontents (dirp->dd_contents);
            errno = ENOMEM;
            return (NULL);
            }
        if (dirp->dd_contents != NULL)
            dirp->dd_cp->_d_next = dp;
        else
            dirp->dd_contents = dp;
        dirp->dd_cp = dp;
        (void)strcpy (dp->_d_entry, s);
        dp->_d_next = NULL;
        dp->_d_size = ((unsigned long)find.size_hi << 16) + find.size_lo;
        dp->_d_mode = find.attr;
        dp->_d_time = find.time;
        dp->_d_date = find.date;
        s = getdirent (NULL);
        } while (s != NULL);
    dirp->dd_cp = dirp->dd_contents;
    return (dirp);
    }


int closedir (DIR *dirp)
    {
    free_dircontents (dirp->dd_contents);
    free (dirp);
    return (0);
    }


static void free_dircontents (struct _dircontents *dp)
    {
    struct _dircontents *odp;

    while (dp != NULL)
        {
        if (dp->_d_entry != NULL)
            free(dp->_d_entry);
        odp = dp;
        dp = dp->_d_next;
        free (odp);
        }
    }


static char *getdirent (char *dir)
    {
    int rc;

    if (dir != NULL)
        rc = __findfirst (dir, A_DIR|A_HIDDEN, &find);
    else
        rc = __findnext (&find);
    if (rc == 0)
        {
        (void)strlwr (find.name);
        return (find.name);
        }
    else
        return (NULL);
    }


static int _readdir_ino = 31415926;

struct dirent *readdir (DIR *dirp)
    {
    static struct dirent dp;

    if (dirp->dd_cp == NULL)
        return (NULL);
    (void)strcpy (dp.d_name, dirp->dd_cp->_d_entry);
    dp.d_namlen = strlen (dp.d_name);
    dp.d_reclen = dp.d_namlen;
    dp.d_ino = _readdir_ino++;
    dp.d_size = dirp->dd_cp->_d_size;
    dp.d_mode = dirp->dd_cp->_d_mode;
    dp.d_time = dirp->dd_cp->_d_time;
    dp.d_date = dirp->dd_cp->_d_date;
    dirp->dd_cp = dirp->dd_cp->_d_next;
    ++dirp->dd_loc;
    return (&dp);
    }


void seekdir (DIR *dirp, long off)
    {
    long i;
    struct _dircontents *dp;

    if (off >= 0)
        {
        i = 0;
        for (dp = dirp->dd_contents; i < off && dp != NULL; dp = dp->_d_next)
            ++i;
        dirp->dd_loc = i;
        dirp->dd_cp = dp;
        }
    else
        errno = EINVAL;
    }


void rewinddir (DIR *dirp)
    {
    seekdir (dirp, 0L);
    }


long telldir (DIR *dirp)
    {
    return (dirp->dd_loc);
    }
