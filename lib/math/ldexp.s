/ ldexp.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _ldexp

        .text

        .align  2, 0x90

/ double ldexp (double x, int exp)

#define x        4(%esp)
#define exp     12(%esp)

_ldexp:
        fildl   exp                     / exp
        fldl    x                       / x
        fscale
        fstp    %st(1)
        ret
