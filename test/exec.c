/* exec.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <signal.h>

static void handler (int sig)
    {
    (void)printf ("Signal %d received. Process stopped.\n", sig);
    exit (1);
    }


int main()
    {
    char buf[100], *p, *q;
    char *nenvp[1];
    char *nargv[100];
    int i, mode;

    (void)signal (SIGINT, handler);
    for (;;)
        {
        printf ("pid=%d\n", (int)getpid ());
        printf ("command: ");
        if (fgets (buf, sizeof (buf), stdin) == NULL)
            {
            perror ("fgets"); return (1);
            }
        p = strchr (buf, '\n');
        if (p != NULL) *p = 0;
        i = 0; p = buf;
        if (strchr (p, '=') != NULL)
            {
            if (putenv (p) != 0)
                perror ("putenv");
            }
        else
            {
            if (*p == '*')
                {
                mode = P_OVERLAY; ++p;
                }
            else if (*p == '#')
                {
                mode = P_DEBUG; ++p;
                }
            else
                mode = P_WAIT;
            if (*p == 0)
                {
                printf ("done\n");
                return (0);
                }
            q = p;
            while ((nargv[i++] = strtok (q, " \t")) != NULL)
                q = NULL;
            nenvp[0] = NULL;
            i = spawnvpe (mode, p, (const char * const *)nargv,
#if 0
                                   NULL);
#else
                                   (const char * const *)nenvp);
#endif
            if (i < 0)
                perror ("spawnve");
            else
                (void)printf ("rc=%d\n", i);
            }
        }
    return (1);
    }
