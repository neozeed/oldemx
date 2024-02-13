/* showmem.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <os2.h>

int main (void)
    {
    ULONG rc, size, flags, base, esp;
    char big[10000], *heap;

    heap =malloc (1);
    big[0] = 0;
    base = 0x10000;
    esp = (ULONG)&esp;
    for (;;)
        {
        size = 0xffffffff;
        rc = DosQueryMem ((PVOID)base, &size, &flags);
        if (rc != 0)
            {
            (void)printf ("DosQueryMem failed, rc=%lu\n", rc);
            return (1);
            }
        (void)printf ("%.8lx - %.8lx (%.8lx)", base, base + size - 1, size);
        if (flags & PAG_FREE)    (void)printf (" FREE  ");
        if (flags & PAG_COMMIT)  (void)printf (" COMMIT");
        if (flags & PAG_GUARD)   (void)printf (" GUARD ");
        if (flags & PAG_SHARED)  (void)printf (" share ");
        if (flags & PAG_READ)    (void)printf (" read  ");
        if (flags & PAG_READ)    (void)printf (" write ");
        if (flags & PAG_EXECUTE) (void)printf (" exec  ");
        if (base <= esp && esp < base + size) (void)printf ("<-- ESP");
        (void)putchar ('\n');
        base += size;
        if (base == 0) break;
        }
    return (0);
    }
