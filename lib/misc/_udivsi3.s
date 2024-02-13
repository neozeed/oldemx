/ _udivsi3.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

        .globl  ___udivsi3

        .align  2, 0x90

___udivsi3:
        movl    1*4(%esp), %eax
        xorl    %edx, %edx
        divl    2*4(%esp)
        ret
