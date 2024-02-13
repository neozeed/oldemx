/* pid.c */

#include <process.h>

int main (void)
    {
    int pid;

    pid = getpid ();
    (void)printf ("pid=%d\n", pid);
    return (0);
    }
