/ exp.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .data

        .comm exp_cw1, 2
        .comm exp_cw2, 2

        .globl  _exp, __exp2

        .text

        .align  2

/ double exp (double x)

_exp:
        fldl    4(%esp)                 / x
        fldl2e                          / log2 (e)
        fmulp                           / x * log2 (e)
        fstpl   4(%esp)

/ double _exp2 (double x)

__exp2:
        fstcww  exp_cw1
        movw    exp_cw1, %ax            / wait inserted by gas
        andw    $0xf3ff, %ax
        orw     $0x0400, %ax            / round down towards -inf
        movw    %ax, exp_cw2
        fldcww  modf_cw2
        fldl    4(%esp)                 / x
        fldl    %st                     / x, x
        frndint                         / int (x), x
        fldcww  exp_cw1
        fxch    %st(1)                  / x, int (x)
        fsub    %st(1), %st             / frac (x), int (x)
        f2xm1                           / 2 ^ frac (x) - 1, int (x)
        fld1                            / 1, 2 ^ frac (x) - 1, int (x)
        faddp                           / 2 ^ frac (x), int (x)
        fscale                          / 2 ^ frac (x) * 2 ^ int (x), int (x)
        fstp    %st(1)                  / 2 ^ frac (x) * 2 ^ int (x)
        ret
