/ modf.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _modf

        .text

        .align  2, 0x90

/ double modf (double x, double *intptr)

#define cw1       0(%esp)
#define cw2       2(%esp)
/define ret_addr  4(%esp)
#define x         8(%esp)
#define intptr   16(%esp)

_modf:
        subl    $4, %esp
        fstcww  cw1
        movw    cw1, %ax                / wait inserted by gas
        orw     $0x0c00, %ax            / chop mode
        movw    %ax, cw2
        movl    intptr, %eax
        fldcww  cw2
        fldl    x                       / x
        fldl    %st
        frndint
        fstl    (%eax)
        fldcww  cw1
        fsubrp
        addl    $4, %esp
        ret
