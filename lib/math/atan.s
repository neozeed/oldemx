/ atan.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _atan

        .text

        .align  2, 0x90

/ double atan (double x)

#define x       4(%esp)

_atan:
        fldl    x                       / x
        fld1
        fpatan
        ret
