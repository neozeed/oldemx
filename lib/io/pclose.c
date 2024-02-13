/* pclose.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdio.h>
#include <process.h>
#include <errno.h>

int pclose (FILE *stream)
    {
    int rc, pid, write_mode;

    if (!(stream->flags & _IOOPEN))
        {
        errno = EBADF;
        return (-1);
        }
    write_mode = (stream->flags & _IOWRT);
    if (write_mode && fclose (stream) != 0)
        return (-1);
    for (;;)
        {
        pid = wait (&rc);
        if (pid == -1)
            return (-1);
        if (pid == stream->pid)
            break;
        }
    if (!write_mode && fclose (stream) != 0 && errno != EBADF)
        return (-1);
    return (rc);
    }
