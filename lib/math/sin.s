/ sin.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _sin

        .text

        .align  2, 0x90

/ double sin (double x)

#define x       4(%esp)

_sin:
        fldl    x                       / x
        fsin                            / sin(x)
        ret
