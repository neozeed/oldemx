/* sig2.c */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

#define FALSE 0
#define TRUE  1

typedef char boolean;

static boolean exit_flag = FALSE;
static boolean recursion_flag = FALSE;
static boolean jump_flag = FALSE;
static boolean key_flag = FALSE;
static boolean kill_flag = FALSE;
static boolean quit_flag = FALSE;
static char level = 'A' - 1;
static jmp_buf jump;

static void handler (int sig)
    {
    int i;

    if (exit_flag)
        exit (0);
    if (kill_flag)
        {
        (void)putchar ('k');
        (void)signal (sig, SIG_DFL);
        (void)signal (sig, SIG_ACK);
        (void)kill (getpid (), sig);
        }
    if (jump_flag)
        longjmp (jump, 1);
    if (quit_flag)
        {
        if (raise (SIGQUIT) != 0)
            perror ("\nraise (SIGQUIT)");
        }
    (void)signal (sig, SIG_ACK);
    (void)putchar ('\a');
    if (recursion_flag)
        {
        ++level;
        for (i = 0; i < 2000; ++i)
            (void)putchar (level);
        (void)putchar ('\n');
        --level;
        }
    }

int main (int argc, char *argv[])
    {
    int i;

    if (setjmp (jump) != 0)
        {
        (void)puts ("jumped");
        return (0);
        }
    for (i = 1; i < argc; ++i)
        if (strcmp (argv[i], "-e") == 0)
            exit_flag = TRUE;
        else if (strcmp (argv[i], "-i") == 0)
            kill_flag = TRUE;
        else if (strcmp (argv[i], "-j") == 0)
            jump_flag = TRUE;
        else if (strcmp (argv[i], "-k") == 0)
            key_flag = TRUE;
        else if (strcmp (argv[i], "-q") == 0)
            quit_flag = TRUE;
        else if (strcmp (argv[i], "-r") == 0)
            recursion_flag = TRUE;
        else
            {
            (void)puts ("Usage: sig2 [-e] [-i] [-j] [-k] [-q] [-r]");
            return (1);
            }
    if (signal (SIGINT, handler) == SIG_ERR)
        {
        (void)puts ("signal failed");
        return (1);
        }
    if (key_flag)
        {
        int c;

        for (;;)
            {
            c = _read_kbd (0, 1, 0);
            if (c == 0)
                (void)_read_kbd (0, 1, 0);
            else if (c == 0x1b)
                break;
            else
                (void)putchar (c);
            }
        }
    else
        {
        for (i = 0; i < 10000; ++i)
            (void)putchar ('.');
        }
    (void)putchar ('\n');
    return (0);
    }
