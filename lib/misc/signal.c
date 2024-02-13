/* signal.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <signal.h>

void (*signal (int sig, void (*handler)()))(int sig)
    {
    return (__signal (sig, handler));
    }
