/ ceil.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  _ceil

        .text

        .align  2, 0x90

/ double ceil (double x)

#define cw1       0(%esp)
#define cw2       2(%esp)
/define ret_addr  4(%esp)
#define x         8(%esp)

_ceil:
        subl    $4, %esp
        fstcww  cw1
        movw    cw1, %ax                / wait inserted by gas
        andw    $0xf3ff, %ax
        orw     $0x0800, %ax            / round up towards +inf
        movw    %ax, cw2
        fldcww  cw2
        fldl    x                       / x
        frndint
        fldcww  cw1
        addl    $4, %esp
        ret
