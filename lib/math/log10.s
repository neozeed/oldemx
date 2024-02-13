/ log10.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _log10

        .text

        .align  2, 0x90

/ double log10 (double x)

#define x       4(%esp)

_log10:
        fldl2t
        fld1
        fdivp
        fldl    x                       / x
        fyl2x
        ret
