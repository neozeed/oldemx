/ asin.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _asin

        .text

        .align  2, 0x90

/ double asin (double x)

/ asin(x) = atan (x / sqrt (1-x*x))

#define x       4(%esp)

_asin:
        fldl    x                       / x
        fld     %st
        fld     %st
        fmulp
        fld1
        fsubp
        fsqrt
        fdivrp
        fld1
        fpatan
        ret
