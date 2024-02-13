/ sin.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _sin

        .text

        .align  2

/ double sin (double x)

_sin:
        fldl    4(%esp)                 / x
        fsin
        ret
