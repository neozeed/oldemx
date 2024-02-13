/ fabs.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _fabs

        .text

        .align  2, 0x90

/ double fabs (double x)

#define x       4(%esp)

_fabs:
        fldl    x                       / x
        fabs
        ret
