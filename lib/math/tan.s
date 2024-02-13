/ tan.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _tan

        .text

        .align  2, 0x90

/ double tan (double x)

#define x       4(%esp)

_tan:
        fldl    x                       / x
        fptan
        fdivrp
        ret
