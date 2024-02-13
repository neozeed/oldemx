/ tan.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _tan

        .text

        .align  2

/ double tan (double x)

_tan:
        fldl    4(%esp)                 / x
        fptan
        fdivrp
        ret
