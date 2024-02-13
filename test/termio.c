/* termio.c */

/* Test termio ioctl() and signals */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <errno.h>
#include <signal.h>
#include <process.h>
#include <sys/termio.h>

static void handler (int sig)
    {
    if (sig == SIGINT)
        {
        (void)printf ("(SIGINT)");
        (void)signal (sig, SIG_ACK);
        }
    else if (sig == SIGALRM)
        {
        (void)printf ("(SIGALRM)");
        (void)signal (sig, SIG_ACK);
        }
    else
        {
        (void)printf ("Signal %d received. Process stopped.\n", sig);
        exit (1);
        }
    }

int main (void)
    {
    char buf[100], *p;
    int n, req;
    struct termio tio;

    (void)signal (SIGINT, handler);
    (void)signal (SIGBREAK, handler);
    (void)signal (SIGQUIT, handler);
    (void)signal (SIGALRM, handler);
    (void)ioctl (0, TCGETA, &tio);
    tio.c_iflag &= ~IDEFAULT;
    (void)ioctl (0, TCSETA, &tio);
    req = sizeof (buf) - 1;
    for (;;)
        {
        n = read (0, buf, req);
        if (n < 0)
            perror ("read");
        if (n >= 0)
            {
            (void)write (1, "<", 1);
            (void)write (1, buf, n);
            (void)write (1, ">\n", 2);
            }
        if (n > 0)
            {
            buf[n] = 0;
            p = strchr (buf, '\n');
            if (p != NULL) *p = 0;
            if (buf[0] == '?')
                {
                (void)puts ("?          Help");
                (void)puts ("$          Quit");
                (void)puts ("!CMD       Shell escape");
                (void)puts ("+          Toggle ICANON");
                (void)puts (":          Toggle IDEFAULT");
                (void)puts ("%SEC       Set alarm clock");
                (void)puts ("#SEC       Sleep");
                (void)puts ("=CHARS     Set number of characters to read");
                (void)puts (">CHARS     Set VMIN");
                (void)puts ("<TENTHS    Set VTIME");
                (void)puts (".SIG       Ignore signal");
                (void)puts ("*SIG       Handle signal");
                (void)puts ("^SIG       Set default processing for signal");
                (void)puts ("~SIG       Raise signal");
                }
            else if (buf[0] == '$')
                break;
            else if (buf[0] == '!')
                system (buf+1);
            else if (buf[0] == '%')
                (void)printf ("alarm=%u\n", alarm (atoi (buf+1)));
            else if (buf[0] == '#')
                {
                n = atoi (buf+1);
                if (n > 0)
                    (void)sleep (n);
                }
            else if (buf[0] == '+')
                {
                tio.c_iflag ^= ICANON;
                (void)ioctl (0, TCSETA, &tio);
                }
            else if (buf[0] == ':')
                {
                tio.c_iflag ^= IDEFAULT;
                (void)ioctl (0, TCSETA, &tio);
                }
            else if (buf[0] == '-')
                {
                tio.c_iflag &= ~ICANON;
                (void)ioctl (0, TCSETA, &tio);
                }
            else if (buf[0] == '>')
                {
                tio.c_cc[VMIN] = (unsigned char)atoi (buf+1);
                (void)ioctl (0, TCSETA, &tio);
                }
            else if (buf[0] == '<')
                {
                tio.c_cc[VTIME] = (unsigned char)atoi (buf+1);
                (void)ioctl (0, TCSETA, &tio);
                }
            else if (buf[0] == '.')
                (void)signal (atoi (buf+1), SIG_IGN);
            else if (buf[0] == '*')
                (void)signal (atoi (buf+1), handler);
            else if (buf[0] == '^')
                (void)signal (atoi (buf+1), SIG_DFL);
            else if (buf[0] == '~')
                (void)raise (atoi (buf+1));
            else if (buf[0] == '=')
                {
                n = atoi (buf+1);
                if (n >= 1 && n <= sizeof (buf) - 1)
                    req = n;
                else
                    req = sizeof (buf) - 1;
                }
            }
        }
    return (0);
    }
