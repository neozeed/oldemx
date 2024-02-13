/ fabs.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _fabs

        .text

        .align  2

/ double fabs (double x)

_fabs:
        fldl    4(%esp)                 / x
        fabs
        ret
