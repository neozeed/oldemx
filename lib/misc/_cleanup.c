/* _cleanup.c (emx/gcc) */

#include <sys/emx.h>
#include <stdio.h>

void _cleanup (void)
    {
    flushall ();
    rmtmp ();
    }
