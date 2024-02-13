/* select.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <io.h>

int select (int nfds, fd_set *readfds, fd_set *writefds,
            fd_set *exceptfds, struct timeval *timeout)
    {
    struct _select args;
    int i, j, n, rc;
    struct timeval tv;
    fd_set tmp;

    args.nfds = nfds;
    args.readfds = readfds;
    args.writefds = writefds;
    args.exceptfds = exceptfds;
    args.timeout = timeout;
    n = min (FD_SETSIZE, _nfiles);
    if (readfds != NULL)
        {
        FD_ZERO (&tmp);         /* no handles ready due to look ahead */
        j = 0;
        for (i = 0; i < n; ++i)
            if (FD_ISSET (i, readfds) && _lookahead[i] >= 0)
                {
                FD_SET (i, &tmp);       /* handles ready due to look ahead */
                ++j;
                }
        if (j != 0)             /* there are handles with active look ahead */
            {
            tv.tv_sec = 0; tv.tv_usec = 0;      /* immediately return */
            args.timeout = &tv;
            rc = __select (&args);
            if (rc == -1)
                return (-1);
            else if (rc == 0)   /* no handles ready -> use look ahead */
                *readfds = tmp;
            else                /* merge */
                for (i = 0; i < n; ++i)
                    if (FD_ISSET (i, &tmp))
                        FD_SET (i, readfds);
            return (rc);
            }
        }
    return (__select (&args));
    }
