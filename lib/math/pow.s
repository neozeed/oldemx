/ pow.s (emx/gcc) -- Copyright (c) 1991-1992 by Kolja Elsaesser
/                    Modified 1992 by Eberhard Mattes

        .data

cmp_zero:
        .double 0d0.00000000000000000000e+000

        .globl  _pow

        .text

        .align  2, 0x90

/ double pow (double x, double y)

#define cw1           -8(%ebp)
#define cw2           -6(%ebp)
#define int_exponent  -4(%ebp)
/define saved_ebp      0(%ebp)
/define ret_addr       4(%ebp)
#define x              8(%ebp)
#define y             16(%ebp)

_pow:   pushl   %ebp
        movl    %esp, %ebp
        subl    $8, %esp
        pushf                           / Save flags
        fstcww  cw1
        movw    cw1, %ax                / wait inserted by gas
        andw    $0xf3ff, %ax            / round nearest zero
        movw    %ax, cw2
        fldl    y
        fldl    x
        fcoml   cmp_zero
        fnstsww %ax
        sahf
        jz      zero
        jc      negative

positive:
        fyl2x                           / y * ln(x)
        fld     %st
        fldcww  cw2
        frndint
        fldcww  cw1
        fsubr   %st, %st(1)
        fxch    %st(1)
        f2xm1
        fld1
        faddp
        fscale
        fxch    %st(1)
        ffree   %st
        fincstp
        jmp     return

        .align  2, 0x90
zero:
        fldl    %st(1)
        fcompl  cmp_zero
        fnstsww %ax
        sahf
        jz      positive        / 0^0           -> NAN
        jc      positive        / 0^negative    -> NAN
        ffree   %st
        fincstp
        ffree   %st
        fincstp
        fldz
        jmp     return

        .align  2, 0x90
negative:
        fld     %st(1)
        fldcww  cw2
        frndint
/ Copy integral part of exponent to memory
        fld     %st
        fistpll int_exponent
        fldcww  cw1
        fsub    %st(2), %st
        fcompl  cmp_zero
        fstsww  %ax
        sahf
/ Non-integral exponent -> error
        jnz     positive
/ Integral exponent -> special case
/ Compute x^y where x is positive
        fchs
        fyl2x                           / y * ln(x)
        fld     %st
        fldcww  cw2
        frndint
        fldcww  cw1
        fsubr   %st, %st(1)
        fxch    %st(1)
        f2xm1
        fld1
        faddp
        fscale
        fxch    %st(1)
        ffree   %st
        fincstp
/ Correction for odd exponent and negative base
        testl   $1, int_exponent
        jz      even_exp
        fchs
        .align  4, 0x90
even_exp:
return: popf
        leave
        ret
