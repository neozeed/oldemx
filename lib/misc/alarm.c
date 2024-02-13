/* alarm.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>

unsigned alarm (unsigned sec)
    {
    return (__alarm (sec));
    }
