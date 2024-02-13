/* debug.c */

/* Test ptrace() */

#include <stdio.h>
#include <string.h>
#include <process.h>
#include <errno.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/reg.h>

struct reg
    {
    char *name;
    int regno;
    unsigned int value;
    };

#define N_EIP 8

static struct reg regs[] =
    {
        {"eax", EAX},
        {"ebx", EBX},
        {"ecx", ECX},
        {"edx", EDX},
        {"esi", ESI},
        {"edi", EDI},
        {"esp", UESP},
        {"ebp", EBP},
        {"eip", EIP},
        {NULL, 0}
    };

static int pid;
static int silent;

static void show_regs (void)
    {
    int i, j, r;
    int uaddr;
    struct user u;

    uaddr = ptrace (PTRACE_PEEKUSER, pid, (char *)&u.u_ar0 - (char *)&u, 0);
    if (errno != 0) perror ("ptrace");
    uaddr -= 0xe0000000;
    j = 4;
    for (i = 0; regs[i].name != NULL; ++i)
        {
        errno = 0;
        r = ptrace (PTRACE_PEEKUSER, pid, uaddr + regs[i].regno * 4, 0);
        if (errno != 0) perror ("ptrace");
        regs[i].value = r;
        if (j == 4)
            {
            j = 0; putchar ('\n');
            }
        ++j;
        printf ("%s=%.8x ", regs[i].name, r);
        }
    errno = 0;
    r = ptrace (PTRACE_PEEKTEXT, pid, regs[N_EIP].value, 0);
    if (errno == 0)
        for (i = 0; i < 4; ++i)
            {
            printf ("%.2x ", r & 0xff);
            r >>= 8;
            }
    putchar ('\n');
    }


static void run (int cmd)
    {
    int s, t, p;

    s = ptrace (cmd, pid, 0, 0);
    if (s < 0)
        perror ("ptrace");
    else
        {
        p = wait (&t);
        if (p == -1)
            perror ("wait");
        if (!silent)
            printf ("wait: %.4x\n", t);
        if ((t & 0377) != 0177)
            {
            printf ("Program terminated (%d)\n", (t >> 8) & 0xff);
            exit (0);
            }
        }
    }

int main (int argc, char **argv, char **envp)
    {
    char buf[10];
    int i;

    i = 1; silent = 0;
    while (i < argc)
        {
        if (strcmp (argv[i], "-s") == 0)
            {
            silent = 1; ++i;
            }
        else
            break;
        }
    if (i+1 > argc)
        {
        fputs ("usage: emx debug [-s] prog [args]\n", stderr);
        exit (1);
        }
    pid = spawnve (P_DEBUG, argv[i], (const char * const *)(argv+i),
                                     (const char * const *)envp);
    if (pid < 0)
        {
        perror ("spawnve");
        exit (2);
        }
    printf ("pid=%d\n", pid);
    for (;;)
        {
        if (silent)
            run (PTRACE_STEP);
        else
            {
            show_regs ();
            if (fgets (buf, sizeof (buf), stdin) == NULL)
                break;
            if (buf[0] == 'g')
                run (PTRACE_RESUME);
            else
                run (PTRACE_STEP);
            }
        }
    return (0);
    }
