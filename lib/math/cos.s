/ cos.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _cos

        .text

        .align  2, 0x90

/ double cos (double x)

#define x       4(%esp)

_cos:
        fldl    x                       / x
        fcos                            / cos(x)
        ret
