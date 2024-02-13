/* stat.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

int stat (const char *name, struct stat *buffer)
    {
    static int stat_ino = 0x100000;
    int handle, result, attr;

    attr = __chmod (name, 0, 0);            /* Get attributes */
    if (attr == -1)
        {
        errno = ENOENT;
        return (-1);
        }
    if (attr & 0x10)                        /* Directory */
        {
        buffer->st_dev = 0;                 /*...*/
        buffer->st_atime = 0;               /*...*/
        buffer->st_mode = S_IFDIR;
        buffer->st_ino = stat_ino++;
        buffer->st_nlink = 1;                       /* One link */
        buffer->st_uid = 0;                         /* We're root! */
        buffer->st_gid = 0;
        buffer->st_rdev = buffer->st_dev;
        buffer->st_mode |= ((S_IREAD|S_IWRITE)>>6)*0111;
        buffer->st_ctime = buffer->st_mtime = buffer->st_atime;
        buffer->st_size = 0;
        return (0);
        }
    handle = open (name, O_RDONLY);
    if (handle < 0)
        {
        errno = ENOENT;
        return (-1);
        }
    result = fstat (handle, buffer);
    close (handle);
    if (buffer->st_ino == handle)
        buffer->st_ino = stat_ino++;        /* All files are different */
    return (result);
    }
