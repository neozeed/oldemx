/ cos.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _cos

        .text

        .align  2

/ double cos (double x)

_cos:
        fldl    4(%esp)                 / x
        fcos
        ret
