/ sqrt.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _sqrt

        .text

        .align  2

/ double sqrt (double x)

_sqrt:
        fldl    4(%esp)                 / x
        fsqrt
        ret
