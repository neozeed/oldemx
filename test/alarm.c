/* alarm.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

static void handler (int sig)
    {
    (void)printf ("Signal %d received. Process stopped.\n", sig);
    exit (1);
    }

int main (void)
    {
    int c;

    (void)signal (SIGALRM, handler);
    (void)alarm (4);
    for (;;)
        {
        c = _read_kbd (0, 0, 0);
        if (c == 0)
            (void)_read_kbd (0, 1, 0);
        else if (c == 0x1b)
            break;
        else if (c >= '0' && c <= '9')
            (void)printf ("alarm=%d\n", alarm (c - '0'));
        }
    return (0);
    }
