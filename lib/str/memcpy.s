/ memcpy.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

        .globl _memcpy

/ void *memcpy (void *s1, const void *s2, size_t n)
/     {
/     size_t i;
/   
/     for (i = 0; i < n; ++i)
/         ((char *)s1)[i] = ((char *)s2)[i];
/     return (s1);
/     }

/ assumes ds=es!

        .text
        .align  2, 0x90

_memcpy:
        pushl   %esi
        pushl   %edi
        movl    3*4(%esp), %edi         / s1
        movl    4*4(%esp), %esi         / s2
        movl    5*4(%esp), %ecx         / n
        rep
        movsb
        movl    3*4(%esp), %eax         / s1
        popl    %edi
        popl    %esi
        ret
