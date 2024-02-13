/* sig1.c */

/* Expected output: +s-+s--+s+s+s-x */

#include <stdio.h>
#include <signal.h>

volatile int ack;

void handler (int sig)
    {
    (void)putchar ('s');
    if (ack)
        signal (sig, SIG_ACK);
    }

void make_stack (void)
    {
    char dummy[50000];
    }

int main (void)
    {
    make_stack ();
    if (signal (SIGINT, handler) == SIG_ERR)
        {
        (void)puts ("signal failed");
        return (1);
        }
    ack = 0;
    (void)putchar ('+');
    (void)raise (SIGINT);
    (void)putchar ('-');
    (void)raise (SIGINT);
    (void)putchar ('+');
    (void)signal (SIGINT, SIG_ACK);
    (void)putchar ('-');
    (void)raise (SIGINT);
    (void)putchar ('-');
    (void)raise (SIGINT);
    ack = 1;
    (void)putchar ('+');
    (void)signal (SIGINT, SIG_ACK);
    (void)putchar ('+');
    (void)raise (SIGINT);
    (void)putchar ('+');
    (void)raise (SIGINT);
    (void)signal (SIGINT, SIG_IGN);
    (void)putchar ('-');
    (void)raise (SIGINT);
    (void)signal (SIGINT, SIG_DFL);
    (void)putchar ('x');
    /* (void)signal (SIGINT, SIG_ACK); */
    (void)raise (SIGINT);
    return (0);
    }
