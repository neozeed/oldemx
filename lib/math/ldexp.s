/ ldexp.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _ldexp

        .text

        .align  2

/ double ldexp (double x, int exp)

_ldexp:
        fildl   12(%esp)                / exp
        fldl    4(%esp)                 / x
        fscale
        fstp    %st(1)
        ret
