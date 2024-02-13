/ div.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

        .globl _div, _ldiv

        .text
        .align  2

/ div_t div (int num, int den)
/ ldiv_t ldiv (long num, long den)

_ldiv:
_div:   movl    1*4(%esp), %eax         / num
        xorl    %edx, %edx
        idivl   2*4(%esp)               / den
        ret
