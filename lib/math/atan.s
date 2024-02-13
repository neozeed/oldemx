/ atan.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _atan

        .text

        .align  2

/ double atan (double x)

_atan:
        fldl    4(%esp)                 / x
        fld1
        fpatan
        ret
