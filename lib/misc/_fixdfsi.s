/ _fixdfsi.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

        .globl  ___fixdfsi

        .align  2, 0x90

___fixdfsi:
        pushl   %ebp
        movl    %esp, %ebp
        subl    $12, %esp
        fstcw   -4(%ebp)  
        movw    -4(%ebp), %ax
        orw     $0x0c00, %ax            / truncate towards zero
        movw    %ax, -2(%ebp) 
        fldcw   -2(%ebp)     
        fldl    8(%ebp)
        fistpl  -12(%ebp)    
        fldcw   -4(%ebp)     
        movl    -12(%ebp), %eax
        leave
        ret
