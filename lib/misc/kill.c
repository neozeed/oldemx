/* kill.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <signal.h>

int kill (int pid, int sig)
    {
    return (__kill (pid, sig));
    }
