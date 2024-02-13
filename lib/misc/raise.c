/* raise.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <signal.h>

int raise (int sig)
    {
    return (__raise (sig));
    }
