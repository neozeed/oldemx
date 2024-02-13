/* memtest.c */

#include <sys/emx.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

#define N 4

static char *check[] =
    {
    "ok", "empty", "bad begin", "bad node", "bad end", "bad rover"
    };

int main ()
    {
    char buf[256], *p;
    void *table[N];
    int idx;
    int i, n;

    for (i = 0; i < N; ++i)
        table[i] = NULL;
    idx = 0;
    for (;;)
        {
        n = (int)sbrk (0);
        prts ("sbrk = "); prti (n); prtc ('\n');
        for (i = 0; i < N; ++i)
            {
            if (i == idx) prtc ('*');
            prti (i); prtc (':'); prti ((int)table[i]); prts ("  ");
            }
        prts ("\n? ");
        i = read (0, buf, sizeof (buf));
        if (i < 0)
            {
            prts ("input failed\n"); return (1);
            }
        buf[i] = 0;
        p = strchr (buf, '\n');
        if (p != NULL) *p = 0;
        if (buf[0] == 'q')
          return (0);
        else if (buf[0] == 'f')
            {
            prts ("free\n");
            free (table[idx]); table[idx] = NULL;
            }
        else if (buf[0] == 'c')
            {
            prts (check[_heapset ('/')]);
            prtc ('\n');
            }
        else if (buf[0] == 't')
            {
            /* provoke exception */
            char *x;
            x = (char *)0x12345678;
            ++*x;
            }
        else if (buf[0] == 0)
            idx = (idx+1)%N;
        else
            {
            i = atoi (buf);
            p = malloc (i);
            if (p == NULL)
                prts ("malloc failed\n");
            else
                {
                table[idx] = p;
                memset (p, '*', i);
                }
            }
        }
    }
