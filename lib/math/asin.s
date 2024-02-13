/ asin.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _asin

        .text

        .align  2

/ double asin (double x)

/ asin(x) = atan (x / sqrt (1-x*x))

_asin:
        fldl    4(%esp)                 / x
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
