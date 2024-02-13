/ setjmp.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

        .globl _setjmp, _longjmp

        .text
        .align  2, 0x90

#define J_EBX  0
#define J_ESI  4
#define J_EDI  8
#define J_ESP 12
#define J_EBP 16
#define J_EIP 20

/ Words at offsets 24..44 are reserved

/ int setjmp (jmp_buf here)

_setjmp:
        movl    1*4(%esp), %edx         / here
        movl    %ebx, J_EBX(%edx)
        movl    %esi, J_ESI(%edx)
        movl    %edi, J_EDI(%edx)
        movl    %ebp, J_EBP(%edx)
        movl    %esp, J_ESP(%edx)
        movl    0*4(%esp), %eax         / return address
        movl    %eax, J_EIP(%edx)
        xorl    %eax, %eax
        ret

/ void longjmp (jmp_buf there, int n)

_longjmp:
        call    ___unwind               / unwind signal handlers
        movl    1*4(%esp), %edx         / there
        movl    2*4(%esp), %eax         / n
        orl     %eax, %eax
        jne     longjmp1
        incl    %eax
longjmp1:
        movl    J_EBX(%edx), %ebx
        movl    J_ESI(%edx), %esi
        movl    J_EDI(%edx), %edi
        movl    J_EBP(%edx), %ebp
        movl    J_ESP(%edx), %esp
        movl    J_EIP(%edx), %edx
        movl    %edx, 0*4(%esp)         / return address
        ret
