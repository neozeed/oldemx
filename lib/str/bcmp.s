/ bcmp.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

        .globl _bcmp

/ int bcmp (const void *s1, const void *s2, size_t n)
/     {
/     size_t i;
/
/     for (i = 0; i < n; ++i)
/         if (s1[i] != s2[i])
/             return (1);
/     return (0);
/     }

/ assumes ds=es!

        .text
        .align  2, 0x90

_bcmp:
        pushl   %esi
        pushl   %edi
        movl    3*4(%esp), %edi         / s1
        movl    4*4(%esp), %esi         / s2
        movl    5*4(%esp), %ecx         / n
        xorl    %eax, %eax
        jecxz   1f                      / return (0)
        repe
        cmpsb
        je      1f
        incl    %eax                    / return (1)
1:      popl    %edi
        popl    %esi
        ret
