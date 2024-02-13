/ crt0.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

#define SYSCALL(x) movb $x,%ah;call ___syscall

#define EINVAL 22

        .globl  _environ
        .globl  _errno
        .globl  __data
        .globl  __emx_env
        .globl  __emx_vcmp
        .globl  __emx_vprt
        .globl  __heap_base
        .globl  __heap_brk
        .globl  __heap_end
        .globl  __org_environ
        .globl  __osmajor
        .globl  __osminor
        .globl  __osmode
        .globl  __text

        .globl  __exit
        .globl  ___syscall

        .text

__text:
        push    $__data
        call    __dos_init
        jmp     __entry1


___syscall:
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
        testl   $0x200, %ebx
        setne   __osmode
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
        cmpl    $255, %eax      / return code > 255?
        jbe     1f
        movl    $255, %eax      / yes: use 255
1:      SYSCALL(0x4c)
        jmp     __never

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
        .long   0                       / stack base address
        .long   0                       / stack end address
        .long   0                       / reserved
        .long   0                       / reserved
        .long   0                       / reserved
        .byte   0                       / options
        .space  63, 0

/ first element of vector (N_SETA|N_EXT == 21)

        .stabs  "__os2dll", 21, 0, 0, 0xffffffff

        .comm   __start_time, 8             / struct _dtd
        .comm   _errno, 4
        .comm   _environ, 4
        .comm   __org_environ, 4
        .comm   __emx_env, 4
        .comm   __emx_vcmp, 4
        .comm   __emx_vprt, 5
        .comm   __osmajor, 1
        .comm   __osminor, 1
        .comm   __osmode, 1
