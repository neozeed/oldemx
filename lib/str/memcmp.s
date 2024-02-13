/ memcmp.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

        .globl _memcmp

/ int memcmp (const void *s1, const void *s2, size_t n)
/     {
/     size_t i;
/     int d;
/     
/     for (i = 0; i < n; ++i)
/         {
/         d = (int)((unsigned char *)s1)[i] - (int)((unsigned char *)s2)[i];
/         if (d != 0)
/             return (d);
/         }
/     return (0);
/     }

/ assumes ds=es!

        .text
        .align  2, 0x90

_memcmp:
        pushl   %esi
        pushl   %edi
        movl    3*4(%esp), %edi         / s1
        movl    4*4(%esp), %esi         / s2
        movl    5*4(%esp), %ecx         / n
        xorl    %eax, %eax
        jecxz   1f
        repe
        cmpsb
        movb    -1(%esi), %al
        subb    -1(%edi), %al
        movsbl  %al, %eax
1:      popl    %edi
        popl    %esi
        ret
