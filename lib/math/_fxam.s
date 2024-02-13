/ _fxam.s (emx/gcc) -- Copyright (c) 1991-1992 by Eberhard Mattes

        .globl  __fxam

        .text

        .align  2

/ int fxam (double x)

__fxam:
        fldl    4(%esp)                 / x
        fxam
        fstsww  %ax
        ffree   %st(0)
        fincstp
        movl    %eax, %edx
        shrl    $8, %eax
        andl    $7, %eax
        test    $0x4000, %edx
        jz      fxam1
        orl     $8, %eax
fxam1:  ret
