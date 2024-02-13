/ log10.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _log10

        .text

        .align  2

/ double log10 (double x)

_log10:
        fldl2t
        fld1
        fdivp
        fldl    4(%esp)                 / x
        fyl2x
        ret
