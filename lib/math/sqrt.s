/ sqrt.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _sqrt

        .text

        .align  2, 0x90

/ double sqrt (double x)

#define x       4(%esp)

_sqrt:
        fldl    x                       / x
        fsqrt
        ret
