/ modf.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .data

        .comm modf_cw1, 2
        .comm modf_cw2, 2

        .globl  _modf

        .text

        .align  2

/ double modf (double x, double *intptr)

_modf:
        fstcww  modf_cw1
        movw    modf_cw1, %ax           / wait inserted by gas
        orw     $0x0c00, %ax            / chop mode
        movw    %ax, modf_cw2
        movl    12(%esp), %eax          / intptr
        fldcww  modf_cw2
        fldl    4(%esp)                 / x
        fldl    %st
        frndint
        fstl    (%eax)
        fldcww  modf_cw1
        fsubrp
        ret
