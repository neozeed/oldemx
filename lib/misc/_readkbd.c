/* _readkbd.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>

int _read_kbd (int echo, int wait, int sig)
    {
    return (__read_kbd (echo, wait, sig));
    }
