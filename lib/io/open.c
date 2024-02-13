/* open.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/* Bugs: O_TRUNC|O_RDONLY not implemented */
/*       O_TEXT|O_WRONLY  does/can not overwrite Ctrl-Z */

int _fmode_bin;                 /* Set non-zero to make binary mode default */

#define SH_COMPATIBILITY  0x00
#define SH_DENY_BOTH      0x10
#define SH_DENY_WRITE     0x20
#define SH_DENY_READ      0x30
#define SH_DENY_NONE      0x40

int open (const char *name, int oflag, ...)
    {
    va_list va;
    int access, attr, handle, pmode;
    int bits;
    char dummy, new;
    long last;

    access = oflag & O_ACCMODE;
    switch (access)
        {
        case O_RDONLY: access |= SH_DENY_WRITE; break;
        case O_WRONLY: access |= SH_DENY_BOTH; break;
        case O_RDWR:   access |= SH_DENY_BOTH; break;
        }
    new = FALSE;
    handle = __open (name, access);
    if (handle < 0)
        {
        if (errno != ENOENT)    /* file/path not found */
            return (-1);
        if (!(oflag & O_CREAT))
            {
            errno = ENOENT;
            return (-1);
            }
        /* create file */
        new = TRUE;
        attr = 0;
        va_start (va, oflag);
        pmode = va_arg (va, int);
        va_end (va);
        pmode &= umask (0);
        if (!(pmode & S_IWRITE))
            attr |= _A_RDONLY;
        handle = __creat (name, attr);
        if (handle < 0)
            return (-1);
        }
    if (handle >= _nfiles)
        {
        __close (handle);
        errno = EMFILE;
        return (-1);
        }
    if (!new && (oflag & (O_CREAT|O_EXCL)) == (O_CREAT|O_EXCL))
        {
        __close (handle);
        errno = EEXIST;
        return (-1);     /* File exists... error */
        }
    bits = 0;
    if (oflag & O_BINARY)
        /* do nothing */;
    else if (oflag & O_TEXT)
        bits |= O_TEXT;
    else if (_fmode_bin == 0)          /* neither O_TEXT nor O_BINARY given */
        bits |= O_TEXT;
    if (__ioctl1 (handle, 0) & 0x80)
        {
        bits |= F_DEV;
        oflag &= ~O_APPEND;
        }
    bits |= oflag & (O_ACCMODE|O_NDELAY|O_APPEND);
    if (!(bits & F_DEV))
        {
        if (oflag & O_TRUNC)
            {
            if ((oflag & O_ACCMODE) == O_RDWR || (oflag & O_ACCMODE) == O_WRONLY)
                (void)__ftruncate (handle, 0);     /* Truncate file */
            else
                {
                __close (handle);
                errno = ENOENT;
                return (-1);                  /* Not implemented */
                }
            }
        else if ((oflag & O_RDWR) && (oflag & O_TEXT))
            {
            last = __lseek (handle, -1L, SEEK_END);
            if (__read (handle, &dummy, 1) == 1 && dummy == 0x1a)
                (void)__ftruncate (handle, last);      /* Remove Ctrl-Z) */
            (void)__lseek (handle, 0L, SEEK_SET);
            }
        }
    _files[handle] = bits;
    _lookahead[handle] = -1;
    return (handle);
    }
