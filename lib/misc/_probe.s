/ _probe.s (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes

        .globl ___probe

/ void __probe (size_t n)

/ Note: this function does not modify any registers and removes
/       its argument from the stack.
/       Do not call this function from a C program!

        .text
        .align  2, 0x90
___probe:
        xchgl   1*4(%esp), %ebx         / save %ebx, put n into %ebx
        pushl   %eax                    / save %eax
        movl    %esp, %eax
        subl    %ebx, %eax              / low address -> %eax
        andl    $-4, %eax               / round down
        movl    %esp, %ebx              / high address -> %ebx
        .align  2, 0x90
1:      subl    $0x1000, %ebx           / move down
        cmpl    %eax, %ebx              / low address reached?
        jb      2f
        testl   %eax, (%ebx)            / reference the page
        jmp     1b                      / repeat

        .align  2, 0x90
2:      testl   %eax, (%eax)            / reference last page
        popl    %eax                    / restore %eax
        movl    1*4(%esp), %ebx         / restore %ebx
        ret     $4                      / return, remove argument from stack
