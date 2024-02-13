/ floor.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .data

        .comm floor_cw1, 2
        .comm floor_cw2, 2

        .globl  _floor

        .text

        .align  2

/ double floor (double x)

_floor:
        fstcww  floor_cw1
        movw    floor_cw1, %ax          / wait inserted by gas
        andw    $0xf3ff, %ax
        orw     $0x0400, %ax            / round down towards -inf
        movw    %ax, floor_cw2
        fldcww  floor_cw2
        fldl    4(%esp)                 / x
        frndint
        fldcww  floor_cw1
        ret
