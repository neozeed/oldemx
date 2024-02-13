/ memcount.s (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes

        .globl __memcount

/ size_t _memcount (const void *mem, int c, size_t n)
/     {
/     size_t i;
/ 
/     i = 0;
/     while (n > 0)
/         {
/         if (*mem == c) ++i;
/         ++mem; --n;
/         }
/     return (i);
/     }

/ assumes ds=es!

        .text
        .align  2, 0x90

__memcount:
        pushl   %edi
        movl    2*4(%esp), %edi         / mem
        movl    3*4(%esp), %eax         / c
        movl    4*4(%esp), %ecx         / n
        xorl    %edx, %edx
        jecxz   9f
        .align  2, 0x90
1:      repne
        scasb
        jne     9f
        incl    %edx
        orl     %ecx, %ecx
        jne     1b
9:      movl    %edx, %eax
        popl    %edi
        ret
