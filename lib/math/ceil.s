/ ceil.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .data

        .comm ceil_cw1, 2
        .comm ceil_cw2, 2

        .globl  _ceil

        .text

        .align  2

/ double ceil (double x)

_ceil:
        fstcww  ceil_cw1
        movw    ceil_cw1, %ax           / wait inserted by gas
        andw    $0xf3ff, %ax
        orw     $0x0800, %ax            / round up towards +inf
        movw    %ax, ceil_cw2
        fldcww  ceil_cw2
        fldl    4(%esp)                 / x
        frndint
        fldcww  ceil_cw1
        ret
