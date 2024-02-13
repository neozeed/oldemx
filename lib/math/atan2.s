/ atan2.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _atan2

        .text

        .align  2

/ double atan2 (double y, double x)

_atan2:
        fldl    4(%esp)                 / y
        fldl    12(%esp)                / x
        fpatan
        ret
