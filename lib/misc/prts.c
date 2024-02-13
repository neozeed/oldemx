/* prts.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <string.h>
#include <io.h>

void prts (const char *string)
    {
    write (1, string, strlen (string));
    }
