/ acos.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _acos

        .text

        .align  2, 0x90

/ double acos (double x)

/ acos(x) = atan2 (sqrt (1-x*x), x)

#define x       4(%esp)

_acos:
        fldl    x                       / x
        fld     %st
        fmulp
        fld1
        fsubp
        fsqrt
        fldl    x                       / x
        fpatan
        ret
