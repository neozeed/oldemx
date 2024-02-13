/* prtc.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <io.h>

void prtc (char c)
    {
    write (1, &c, 1);
    }
