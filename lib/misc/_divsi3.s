/ _divsi3.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

        .globl  ___divsi3

        .align  2, 0x90

___divsi3:
        movl    1*4(%esp), %eax
        cltd
        idivl   2*4(%esp)
        ret
