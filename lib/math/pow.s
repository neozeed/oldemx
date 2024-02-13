/ pow.s (emx/gcc) -- Copyright (c) 1991-1992 by Kolja Elsaesser

        .data

        .comm pow_cw1, 2
        .comm pow_cw2, 2
        .comm int_exponent, 8

cmp_zero:
        .double 0d0.00000000000000000000e+000

        .globl  _pow

        .text

        .align  2

/ double pow (double x,double y)

_pow:
        fstcww  pow_cw1
        movw    pow_cw1, %ax            / wait inserted by gas
        andw    $0xf3ff, %ax            / round nearest zero
        movw    %ax, pow_cw2
        fldl    12(%esp)                / y
        fldl    4(%esp)                 / x
        fcoml   cmp_zero
        fnstsww %ax
        pushf
        sahf
        jz      zero
        jc      negative

positive:
        popf
        fyl2x                           / y * ln(x)
        fld     %st
        fldcww  pow_cw2
        frndint
        fldcww  pow_cw1
        fsubr   %st,%st(1)
        fxch    %st(1)
        f2xm1
        fld1
        faddp
        fscale
        fxch    %st(1)
        ffree   %st
        fincstp
        ret

zero:
        fldl    %st(1)
        fcompl  cmp_zero
        fnstsww %ax
        sahf
        jz      positive        / 0^0           -> NAN
        jc      positive        / 0^negative    -> NAN
        popf
        ffree   %st
        fincstp
        ffree   %st
        fincstp
        fldz
        ret

negative:
        fld     %st(1)
        fldcww  pow_cw2
        frndint
/ Copy integral part of exponent to memory
        fld     %st
        fistpll int_exponent
        fldcww  pow_cw1
        fsub    %st(2),%st
        fcompl  cmp_zero
        fstsww  %ax
        sahf
/ Non-integral exponent -> error
        jnz     positive
/ Integral exponent -> special case
        popf
/ Compute x^y where x is positive
        fchs
        fyl2x                           / y * ln(x)
        fld     %st
        fldcww  pow_cw2
        frndint
        fldcww  pow_cw1
        fsubr   %st,%st(1)
        fxch    %st(1)
        f2xm1
        fld1
        faddp
        fscale
        fxch    %st(1)
        ffree   %st
        fincstp
/ Correction for odd exponent and negative base
        movl    int_exponent,%eax
        testl   $0x1, %eax
        jz      even_exp
        fchs
even_exp:
        ret
