/* stack.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <alloca.h>

void print_esp (void)
    {
    unsigned long n;

    n = (unsigned long)&n;
    (void)printf ("ESP = %.8lX\n", n);
    }

void mysig (int sig)
    {
    (void)printf ("\n---Signal\n");
    exit (1);
    }

void test (int level)
    {
    int n;
    char buf[10000], *p;

    signal (SIGINT, mysig);   /* DosSetSignalExceptionFocus */
    for (;;)
        {
        print_esp ();
        (void)printf ("Input(%d): ", level); fflush (stdout);
        if (fgets (buf, sizeof (buf), stdin) == NULL)
            exit (0);
        p = strchr (buf, '\n');
        if (p != NULL) *p = 0;
        errno = 0;
        if (buf[0] == 0)
            break;
        if (buf[0] == 'r')
            test (level+1);
        else if ((n = strtol (buf, &p, 0)) > 0 && errno == 0 && *p == 0)
            p = alloca (n);
        else
            (void)printf ("Redo!\n");
        }
    }

int main (void)
    {
    test (1);
    return (0);
    }
