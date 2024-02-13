/ strlen.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

        .globl _strlen

/ size_t strlen (const char *string)
/     {
/     size_t i;
/ 
/     i = 0;
/     while (string[i] != 0) ++i;
/     return (i);
/     }

/ assumes ds=es!

        .text
        .align  2, 0x90

_strlen:
        pushl   %edi
        movl    2*4(%esp), %edi         / string
        movl    $-1, %ecx
        movb    $0, %al
        repne
        scasb
        movl    $-2, %eax
        subl    %ecx, %eax
        popl    %edi
        ret
