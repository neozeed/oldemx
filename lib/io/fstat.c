/* fstat.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>

int fstat (int handle, struct stat *buffer)
    {
    int i;
    struct _ftd ftd;
    struct tm tm;

    if (handle < 0 || handle >= _nfiles)
        {
        errno = EBADF;
        return (-1);
        }
    i = __ioctl1 (handle, 0);
    if (i < 0)
        {
        errno = EBADF;
        return (-1);
        }
    if (i & 0x80)
        {
        buffer->st_dev = handle;    /* Only an approximation */
        buffer->st_mode = S_IFCHR;
        }
    else
        {
        buffer->st_dev = i & 0x1f;              /* Drive number */
        buffer->st_mode = S_IFREG;
        }
    buffer->st_ino = handle;        /* Only an approximation */
    if (_files[handle] & O_RDONLY)
        buffer->st_mode |= (S_IREAD>>6)*0111;
    else
        buffer->st_mode |= ((S_IREAD|S_IWRITE)>>6)*0111;
    buffer->st_nlink = 1;                       /* One link */
    buffer->st_uid = 0;                         /* We're root! */
    buffer->st_gid = 0;
    buffer->st_rdev = buffer->st_dev;
    if (buffer->st_mode & S_IFREG)
        {
        long cur;

        cur = __lseek (handle, 0L, SEEK_CUR);
        buffer->st_size = __lseek (handle, 0L, SEEK_END);
        __lseek (handle, cur, SEEK_SET);
        if (__filetime (handle, 0, &ftd) < 0)
            buffer->st_atime = 0;
        else
            {
            tm.tm_sec = ftd.sec;
            tm.tm_min = ftd.min;
            tm.tm_hour = ftd.hour;
            tm.tm_mday = ftd.day;
            tm.tm_mon = ftd.month-1;
            tm.tm_year = ftd.year + 1980 - 1900;
            tm.tm_isdst = 0;
            buffer->st_atime = mktime (&tm);
            }
        buffer->st_ctime = buffer->st_mtime = buffer->st_atime;
        }
    else
        buffer->st_size = 0;
    return (0);
    }
