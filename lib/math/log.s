/ log.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _log

        .text

        .align  2, 0x90

/ double log (double x)

#define x       4(%esp)

_log:
        fldl2e
        fld1
        fdivp
        fldl    x                       / x
        fyl2x
        ret
