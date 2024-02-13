/* hw_io.c (emx/gcc) */

#include <stdio.h>
#include <dos.h>

int inp8 (int port)
    {
    int result;

    asm ("movl %1,%%edx;inb %%dx,%%al;movzbl %%al,%0"
         : "=a"(result) : "g" (port) : "dx");
    return (result);
    }

int main (void)
    {
    if (_portaccess (0x40, 0x40) != 0)
        {
        perror ("_portaccess");
        return (1);
        }
    for (;;)
        printf ("  %.2x", inp8 (0x40));
    return (0);
    }
