/ memset.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

        .globl _memset

/ void *memset (void *s, int c, size_t n)
/     {
/     size_t i;
/ 
/     for (i = 0; i < n; ++i)
/         ((char *)s)[i] = (char)c;
/     return (s);
/     }

/ assumes ds=es!

        .text
        .align  2, 0x90

_memset:
        pushl   %edi
        movl    2*4(%esp), %edi         / s
        movl    3*4(%esp), %eax         / c
        movl    4*4(%esp), %ecx         / n
        rep
        stosb
        movl    2*4(%esp), %eax         / s
        popl    %edi
        ret
