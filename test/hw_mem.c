/* hw_mem.c (emx/gcc) */

#include <stdio.h>
#include <memory.h>
#include <dos.h>

int main (void)
    {
    unsigned char buf[256], *p;
    int i, vmode;
    unsigned base;

    asm ("movb $0x0f,%%ah;int $0x10;movzbl %%al,%0" : "=g"(vmode) : : "ax");
    (void)printf ("Video mode: 0x%.2x\n", vmode);
    if (vmode == 0x0f)
        base = 0xb0000;
    else
        base = 0xb8000;
    p = _memaccess (base, base + 0x7fff);
    if (p == NULL)
        {
        perror ("_memaccess");
        return (1);
        }
    (void)memmove (buf, p, sizeof (buf));
    for (i = 0; i < sizeof (buf); ++i)
        printf ("  %.2x", (int)buf[i]);
    return (0);
    }
