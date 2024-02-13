/* abort.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <io.h>
#include <stdlib.h>
#include <string.h>
/* #include <signal.h> */

void abort (void)
    {
    const char *msg = "Abnormal program termination\n";

    write (1, msg, strlen (msg));
    /* raise (SIGABRT); */
    _exit (3);
    }
