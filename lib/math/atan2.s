/ atan2.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _atan2

        .text

        .align  2, 0x90

/ double atan2 (double y, double x)

#define y        4(%esp)
#define x       12(%esp)

_atan2:
        fldl    y                       / y
        fldl    x                       / x
        fpatan
        ret
