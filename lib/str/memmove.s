/ memmove.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

        .globl _memmove

/ void *memmove (void *s1, const void *s2, size_t n)
/     {
/     size_t i;
/   
/     if ((size_t)s1 < (size_t)s2)
/         for (i = 0; i < n; ++i)
/             ((char *)s1)[i] = ((char *)s2)[i];
/     else
/         for (i = n; i > 0; --i)                          /* i is unsigned! */
/             ((char *)s1)[i-1] = ((char *)s2)[i-1];
/     return (s1);
/     }

/ assumes ds=es!

        .text
        .align  2, 0x90

_memmove:
        pushl   %esi
        pushl   %edi
        movl    3*4(%esp), %edi         / s1
        movl    4*4(%esp), %esi         / s2
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
9:      movl    3*4(%esp), %eax         / s1
        popl    %edi
        popl    %esi
        ret
