/ bzero.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

        .globl _bzero

/ void bzero (void *s, size_t n)
/     {
/     size_t i;
/ 
/     for (i = 0; i < n; ++i)
/         ((char *)s)[i] = 0;
/     }

/ assumes ds=es!

        .text
        .align  2, 0x90

_bzero:
        pushl   %edi
        movl    2*4(%esp), %edi         / s
        movl    3*4(%esp), %ecx         / n
        xorl    %eax, %eax
        rep
        stosb
        popl    %edi
        ret
