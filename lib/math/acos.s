/ acos.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _acos

        .text

        .align  2

/ double asin (double x)

/ acos(x) = atan (sqrt (1-x*x) / x)

_acos:
        fldl    4(%esp)                 / x
        fld     %st
        fld     %st
        fmulp
        fld1
        fsubp
        fsqrt
        fdivp
        fld1
        fpatan
        ret
