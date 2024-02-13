/ crt0.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

#define SYSCALL(x) movb $x,%ah;call __syscall

#define EINVAL 22

        .globl  __data, _errno, _environ, __org_environ
        .globl  __osmajor, __osminor, __emx_vcmp, __emx_vprt, __emx_env
        .globl  __text, __exit, __syscall
        .globl  ___udivsi3, ___divsi3, ___fixdfsi
        .globl  __heap_base, __heap_end, __heap_brk

        .text

__text:
        push    $__data
        call    __dos_init
        jmp     __entry1


__syscall:
        call    __dos_syscall
        ret

__entry1:
        cld
        xorl    %ebp, %ebp      / End of stack frames
        leal    (%esp), %edi    / argv[]
        movl    %edi, _environ
        movl    %edi, __org_environ
        pushl   %edi            / envp
        call    __ptr_tbl
        pushl   %edi            / argv
        call    __ptr_tbl
        pushl   %ecx            / argc
        SYSCALL(0x30)
        movb    %al, __osmajor
        movb    %ah, __osminor
        movb    $10, %al
        SYSCALL(0x7f)
        movl    %eax, __emx_vcmp
        movl    %ebx, __emx_env
        xchgb   %al, %ah
        rorl    $16, %eax
        xchgb   %al, %ah
        movl    %eax, __emx_vprt
        movb    $0, __emx_vprt+4
        call    __startup
        call    _main
        addl    $3*4, %esp
        pushl   %eax
        call    _exit
__never:jmp     __never


__dos_init:
        ret     $4

__dos_syscall:
        int     $0x21
        ret


__ptr_tbl:
        xorl    %eax, %eax
        movl    $-1, %ecx
__pt1:  incl    %ecx
        scasl
        jne     __pt1
        ret


__exit: popl    %ecx            / return address
        popl    %eax            / argument
        SYSCALL(0x4c)

        .align  2

___udivsi3:
        movl    1*4(%esp), %eax
        xorl    %edx, %edx
        divl    2*4(%esp)
        ret

        .align  2

___divsi3:
        movl    1*4(%esp), %eax
        cltd
        idivl   2*4(%esp)
        ret

        .align  2

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

        .data

/ The data segment starts with a table containing the start and end
/ addresses of the text, data and bss segments

__data:
        .long   __text
        .long   __etext
        .long   __data
        .long   __edata
        .long   __edata
        .long   __end
__heap_base:
        .long   0                       / heap base address
__heap_end:
        .long   0                       / heap end address
__heap_brk:
        .long   0                       / heap brk address
        .long   0                       / heap offset
        .long   __os2dll                / list of OS/2 DLL references
        .long   0                       / reserved
        .long   0                       / reserved
        .long   0                       / reserved
        .long   0                       / reserved
        .long   0                       / reserved
        .byte   0                       / options
        .space  63, 0

 / first element of vector (N_SETA|N_EXT == 21)

        .stabs  "__os2dll", 21, 0, 0, 0xffffffff

        .comm   _errno, 4
        .comm   _environ, 4
        .comm   __org_environ, 4
        .comm   __emx_env, 4
        .comm   __emx_vcmp, 4
        .comm   __emx_vprt, 5
        .comm   __start_time, 8             / struct _dtd
        .comm   __osmajor, 1
        .comm   __osminor, 1
