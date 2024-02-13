/* prti.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>
#include <string.h>

void prti (int i)
    {
    char buf[33];

    itoa (i, buf, 10);
    write (1, buf, strlen (buf));
    }
