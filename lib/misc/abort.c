/* abort.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>
#include <signal.h>

static sig_atomic_t abort_flag = 0;

void volatile abort (void)
    {
    if (abort_flag++ == 0)
        _cleanup ();
    (void)raise (SIGABRT);
    _exit (3);                                    /* Should not get reached */
    }
