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

int _fmode = O_TEXT;

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

    va_start (va, oflag);
    access = oflag & O_MODE_MASK;
    switch (access)
        {
        case O_RDONLY: access |= SH_DENY_WRITE; break;
        case O_WRONLY: access |= SH_DENY_BOTH; break;
        case O_RDWR:   access |= SH_DENY_BOTH; break;
        }
    new = FALSE;
    handle = _open (name, access);
    if (handle < 0)
        {
        if (errno != ENOENT)    /* file/path not found */
            {
            errno = EACCES;
            return (-1);
            }
        if (!(oflag & O_CREAT))
            {
            errno = ENOENT;
            return (-1);
            }
        /* create file */
        new = TRUE;
        attr = 0;
        pmode = va_arg (va, int);
        pmode &= umask (0);
        if (!(pmode & S_IWRITE))
            attr |= _A_RDONLY;
        handle = _creat (name, attr);
        if (handle < 0)
            return (-1);
        }
    if (handle >= _NFILES)
        {
        errno = EMFILE;
        return (-1);
        }
    if (!new && (oflag & (O_CREAT|O_EXCL)) == (O_CREAT|O_EXCL))
        {
        _close (handle);
        errno = EEXIST;
        return (-1);     /* File exists... error */
        }
    bits = 0;
    if (oflag & O_BINARY)
        /* do nothing */;
    else if (oflag & O_TEXT)
        bits |= O_TEXT;
    else if (_fmode & O_TEXT)        /* neither O_TEXT nor O_BINARY given */
        bits |= O_TEXT;
    if (_ioctl1 (handle, 0) & 0x80)
        {
        bits |= F_DEV;
        oflag &= ~O_APPEND;
        }
    bits |= oflag & (O_MODE_MASK|O_APPEND);
    if (!(bits & F_DEV))
        {
        if (oflag & O_TRUNC)
            {
            if ((oflag & O_MODE_MASK) == O_RDWR ||
                (oflag & O_MODE_MASK) == O_WRONLY)
                _write (handle, &dummy, 0);     /* Truncate file */
            else
                {
                _close (handle);
                errno = ENOENT;
                return (-1);                  /* Not implemented */
                }
            }
        else if ((oflag & O_RDWR) && (oflag & O_TEXT))
            {
            _lseek (handle, -1L, SEEK_END);
            if (_read (handle, &dummy, 1) == 1 && dummy == 0x1a)
                {
                _lseek (handle, -1L, SEEK_END);
                _write (handle, &dummy, 0);     /* Truncate (remove Ctrl-Z) */
                }
            _lseek (handle, 0L, SEEK_SET);
            }
        }
    _files[handle] = bits;
    return (handle);
    }
