/ exp.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _exp

        .text

        .align  2, 0x90

/ double exp (double x)

#define cw1      0(%esp)
#define cw2      2(%esp)
/define ret_addr 4(%esp)
#define x        8(%esp)

_exp:
        subl    $4, %esp                / space for control words
        fldl    x                       / x
        fldl2e                          / log2 (e)
        fmulp                           / x * log2 (e)
        fstpl   x
        fstcww  cw1
        movw    cw1, %ax                / wait inserted by gas
        andw    $0xf3ff, %ax
        orw     $0x0400, %ax            / round down towards -inf
        movw    %ax, cw2
        fldcww  cw2      
        fldl    x                       / x
        fldl    %st                     / x, x
        frndint                         / int (x), x
        fldcww  cw1
        fxch    %st(1)                  / x, int (x)
        fsub    %st(1), %st             / frac (x), int (x)
        f2xm1                           / 2 ^ frac (x) - 1, int (x)
        fld1                            / 1, 2 ^ frac (x) - 1, int (x)
        faddp                           / 2 ^ frac (x), int (x)
        fscale                          / 2 ^ frac (x) * 2 ^ int (x), int (x)
        fstp    %st(1)                  / 2 ^ frac (x) * 2 ^ int (x)
        addl    $4, %esp                / Remove control words
        ret
