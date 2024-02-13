/ bcopy.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

        .globl _bcopy

/ void bcopy (const void *s1, void *s2, size_t n)
/     {
/     size_t i;
/ 
/     if ((size_t)s1 < (size_t)s2)
/         for (i = n; i > 0; --i)
/             ((char *)s2)[i-1] = ((char *)s1)[i-1];
/     else
/         for (i = 0; i < n; ++i)
/             ((char *)s2)[i] = ((char *)s1)[i];
/     }

/ assumes ds=es!

        .text
        .align  2, 0x90

_bcopy:
        pushl   %esi
        pushl   %edi
        movl    3*4(%esp), %esi         / s1
        movl    4*4(%esp), %edi         / s2
        movl    5*4(%esp), %ecx         / n
        jecxz   9f
        cmpl    %edi, %esi
        jb      1f
        rep
        movsb
        jmp     9f

1:      addl    %ecx, %esi
        addl    %ecx, %edi
        decl    %esi
        decl    %edi
        std
        rep
        movsb
        cld
9:      popl    %edi
        popl    %esi
        ret
