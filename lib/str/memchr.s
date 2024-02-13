/ memchr.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

        .globl _memchr

/ void *memchr (const void *s, int c, size_t n)
/     {
/     size_t i;
/     const char *p;
/
/     p = s;
/     for (i = 0; i < n; ++i)
/         if (p[i] == (char)c)
/             return ((void *)(p+i));
/     return (NULL);
/     }

/ assumes ds=es!

        .text
        .align  2, 0x90

_memchr:
        pushl   %edi
        movl    2*4(%esp), %edi         / s
        movb    3*4(%esp), %al          / c
        movl    4*4(%esp), %ecx         / n
        jecxz   1f                      / not found
        repne
        scasb
        jne     1f                      / not found
        lea     -1(%edi), %eax
        popl    %edi
        ret

1:      xorl    %eax, %eax              / return (NULL)
        popl    %edi
        ret
