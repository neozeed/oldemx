/ log.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _log

        .text

        .align  2

/ double log (double x)

_log:
        fldl2e
        fld1
        fdivp
        fldl    4(%esp)                 / x
        fyl2x
        ret
