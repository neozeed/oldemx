/ syscalls.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

#define SYSCALL(x) movb $x,%ah;call ___syscall

#define EINVAL 22

        .globl  ___alarm
        .globl  ___cgets
        .globl  ___chdir
        .globl  ___chmod
        .globl  ___chdrive
        .globl  ___close
        .globl  ___core
        .globl  ___creat
        .globl  ___dup
        .globl  ___dup2
        .globl  ___fcntl
        .globl  ___filetime
        .globl  ___findfirst
        .globl  ___findnext
        .globl  ___fsync
        .globl  ___ftime
        .globl  ___ftruncate
        .globl  ___getcwd
        .globl  ___getdrive
        .globl  ___getpid
        .globl  ___ioctl1
        .globl  ___ioctl2
        .globl  ___kill
        .globl  ___lseek
        .globl  ___memaccess
        .globl  ___memavail
        .globl  ___mkdir
        .globl  ___open
        .globl  ___pipe
        .globl  ___portaccess
        .globl  ___ptrace
        .globl  ___raise
        .globl  ___read
        .globl  ___read_kbd
        .globl  ___remove
        .globl  ___rename
        .globl  ___rmdir
        .globl  ___sbrk
        .globl  ___scrsize
        .globl  ___select
        .globl  ___signal
        .globl  ___sleep
        .globl  ___spawnve
        .globl  ___swchar
        .globl  ___syserrno
        .globl  ___uflags
        .globl  ___ulimit
        .globl  ___umask
        .globl  ___unwind
        .globl  ___write
        .globl  ___wait


/ return 0 if carry flag is not set
/ set errno and return -1 if carry flag is set

        .align  2, 0x90

sysret0:jb      1f
        xorl    %eax, %eax
        ret
1:      movl    %eax, _errno
        movl    $-1, %eax
        ret

/ return %eax if carry flag is not set
/ set errno and return -1 if carry flag is set

        .align  2, 0x90

sysreteax:
        jnb     1f
        movl    %eax, _errno
        movl    $-1, %eax
1:      ret



/ __open (char *path, int access)

        .align  2, 0x90

___open:
        movb    2*4(%esp), %al          / access
        movl    1*4(%esp), %edx         / path
        SYSCALL(0x3d)
        jmp     sysreteax


/ __creat (char *path, int attr)

        .align  2, 0x90

___creat:
        movl    2*4(%esp), %ecx         / attr
        movl    1*4(%esp), %edx         / path
        SYSCALL(0x3c)
        jmp     sysreteax


/ __close (int handle)

        .align  2, 0x90

___close:
        pushl   %ebx
        movl    2*4(%esp), %ebx         / handle
        SYSCALL(0x3e)
        popl    %ebx
        jmp     sysret0


/ __write (int handle, void *buf, size_t nbyte)

        .align  2, 0x90

___write:
        pushl   %ebx
        movl    4*4(%esp), %ecx         / nbyte
        movl    3*4(%esp), %edx         / buf
        movl    2*4(%esp), %ebx         / handle
        SYSCALL(0x40)
        popl    %ebx
        jmp     sysreteax

/ __read (int handle, void *buf, size_t nbyte)

        .align  2, 0x90

___read:
        pushl   %ebx
        movl    4*4(%esp), %ecx         / nbyte
        movl    3*4(%esp), %edx         / buf
        movl    2*4(%esp), %ebx         / handle
        SYSCALL(0x3f)
        popl    %ebx
        jmp     sysreteax


/ __lseek (int handle, long offset, int origin)

        .align  2, 0x90

___lseek:
        pushl   %ebx
        movb    4*4(%esp), %al          / origin
        movl    3*4(%esp), %edx         / offset
        movl    2*4(%esp), %ebx         / handle
        SYSCALL(0x42)
        popl    %ebx
        jmp     sysreteax


/ __ioctl1 (int handle, int code)

        .align  2, 0x90

___ioctl1:
        pushl   %ebx
        movb    3*4(%esp), %al          / code
        movl    2*4(%esp), %ebx         / handle
        SYSCALL(0x44)
        popl    %ebx
        jb      1f
        movzwl  %dx, %eax
        ret

1:      movl    %eax, _errno
        movl    $-1, %eax
        ret


/ int __chmod (char *name, int flag, int attr)

        .align  2, 0x90

___chmod:
        movl    1*4(%esp), %edx         / name
        movb    2*4(%esp), %al          / flag
        movl    3*4(%esp), %ecx         / attr
        SYSCALL(0x43)
        jb      1f
        movzwl  %cx, %eax
        ret
1:      movl    %eax, _errno
        movl    $-1, %eax
        ret


/ int __remove (const char *name)

        .align  2, 0x90

___remove:
        movl    1*4(%esp), %edx         / name
        SYSCALL(0x41)
        jmp     sysret0

/ int __rename (const char *old_name, const char *new_name)

        .align  2, 0x90

___rename:
        pushl   %edi
        movl    2*4(%esp), %edx         / old_name
        movl    3*4(%esp), %edi         / new_name
        SYSCALL(0x56)
        popl    %edi
        jmp     sysret0


/ int __filetime (int handle, int flag, struct _ftd *date_time)

        .align  2, 0x90

___filetime:
        pushl   %ebx
        movl    4*4(%esp), %ebx         / date_time
        movw    0(%ebx), %cx
        movw    2(%ebx), %dx
        movb    3*4(%esp), %al          / flag
        movl    2*4(%esp), %ebx         / handle
        SYSCALL(0x57)
        jnb     1f
        movl    %eax, _errno
        movl    $-1, %eax
        jmp     2f
1:      xorl    %eax, %eax
        movl    4*4(%esp), %ebx         / date_time
        movw    %cx, 0(%ebx)
        movw    %dx, 2(%ebx)
2:      popl    %ebx
        ret


/ void __ftime (struct _dtd *time_date)

        .align  2, 0x90

___ftime:
        pushl   %ebx
        movl    2*4(%esp), %ebx
1:      SYSCALL(0x2a)                   / Get date
        movb    %dl, 4(%ebx)            / day
        movb    %dh, 5(%ebx)            / month
        movw    %cx, 6(%ebx)            / year
        SYSCALL(0x2c)                   / Get time
        movb    %dl, 0(%ebx)            / hsec
        movb    %dh, 1(%ebx)            / sec
        movb    %cl, 2(%ebx)            / min
        movb    %ch, 3(%ebx)            / hour
/ Read the date again to avoid a problem at midnight
        SYSCALL(0x2a)                   / Get date
        cmpb    %dl, 4(%ebx)            / day
        jne     1b
        cmpb    %dh, 5(%ebx)            / month
        jne     1b
        cmpw    %cx, 6(%ebx)            / year
        jne     1b
        popl    %ebx
        ret


/ int __chdir (const char *name)

        .align  2, 0x90

___chdir:
        movl    1*4(%esp), %edx
        SYSCALL(0x3b)
        jmp     sysret0

/ int __mkdir (const char *name)

        .align  2, 0x90

___mkdir:
        movl    1*4(%esp), %edx
        SYSCALL(0x39)
        jmp     sysret0


/ int __rmdir (const char *name)

        .align  2, 0x90

___rmdir:
        movl    1*4(%esp), %edx
        SYSCALL(0x3a)
        jmp     sysret0


/ int __dup (int handle)

        .align  2, 0x90

___dup:
        pushl   %ebx
        movl    2*4(%esp), %ebx         / handle
        SYSCALL(0x45)
        popl    %ebx
        jmp     sysreteax


/ int __dup2 (int handle1, int handle2)

        .align  2, 0x90

___dup2:
        pushl   %ebx
        movl    2*4(%esp), %ebx         / handle1
        movl    3*4(%esp), %ecx         / handle2
        SYSCALL(0x46)
        popl    %ebx
        jmp     sysreteax


/ int __getcwd (char *buffer, char drive)

        .align  2, 0x90

___getcwd:
        pushl   %esi
        movl    2*4(%esp), %esi         / buffer
        movb    3*4(%esp), %dl          / drive
        cmpb    $0, %dl
        je      1f
        subl    $0x40, %dl
1:      SYSCALL(0x47)
        popl    %esi
        jmp     sysret0


/ int __findfirst (const char *name, int attr, struct _find *fp)

        .align  2, 0x90

___findfirst:
        pushl   %esi
        movl    2*4(%esp), %edx
        movl    3*4(%esp), %ecx
        movl    4*4(%esp), %esi
        SYSCALL(0x4e)
        popl    %esi
        jmp     sysret0


/ int __findnext (struct _find *fp)

        .align  2, 0x90

___findnext:
        pushl   %esi
        movl    2*4(%esp), %esi
        SYSCALL(0x4f)
        popl    %esi
        jmp     sysret0


/ long __ulimit (int cmd, long new_limit)

        .align  2, 0x90

___ulimit:
        movb    $2, %al
        movl    1*4(%esp), %ecx         / cmd
        movl    2*4(%esp), %edx         / new_limit
        SYSCALL(0x7f)
        jecxz   1f
        movl    %ecx, _errno
1:      ret


/ int __umask (int pmode)

        .align  2, 0x90

___umask:
        movl    1*4(%esp), %edx         / pmode
        movb    $4, %al                 / umask
        SYSCALL(0x7f)
        ret


/ int __uflags (int mask, int new)

        .align  2, 0x90

___uflags:
        movl    1*4(%esp), %ecx         / mask
        movl    2*4(%esp), %edx         / new
        movb    $15, %al                / uflags
        SYSCALL(0x7f)
        ret

/ int __swchar (int flag, int new)

        .align  2, 0x90

___swchar:
        movb    1*4(%esp), %al          / flag
        movb    2*4(%esp), %dl          / new
        SYSCALL(0x37)
        movzbl  %al, %eax
        movb    %dl, %ah
        ret

/ void *__sbrk (int incr)

        .align  2, 0x90

___sbrk:
        movl    1*4(%esp), %edx
        movb    $0, %al
        SYSCALL(0x7f)
        ret


/ int __getpid (void)

        .align  2, 0x90

___getpid:
        movb    $5, %al
        SYSCALL(0x7f)
        ret
        

/ int __spawnve (struct _new_proc *np)

        .align  2, 0x90

___spawnve:
        movl    1*4(%esp), %edx
        movw    %ds, %cx
        movw    %cx, 12(%edx)           / arg_sel
        movw    %cx, 14(%edx)           / env_sel
        movw    %cx, 16(%edx)           / fname_sel
        movb    $0x06, %al
        SYSCALL(0x7f)
        jnb     1f                      / Either process id or return code
        movl    %eax, _errno            / Error code
        movl    $-1, %eax
1:      ret


/ int __raise (int sig)

        .align  2, 0x90

___raise:
        movl    1*4(%esp), %ecx         / sig
        movb    $14, %al                / raise
        SYSCALL(0x7f)
        jecxz   1f
        movl    %ecx, _errno
1:      ret


/ int __kill (int pid, int sig)

        .align  2, 0x90

___kill:
        movl    1*4(%esp), %edx         / pid
        movl    2*4(%esp), %ecx         / sig
        movb    $0x0d, %al              / kill
        SYSCALL(0x7f)
        jecxz   1f
        movl    %ecx, _errno
1:      ret


/ void (*__signal (int sig, void (*handler)()))(int sig)

        .align  2, 0x90

___signal:
        movl    1*4(%esp), %ecx         / sig
        movl    2*4(%esp), %edx         / handler
        movb    $0x0c, %al              / signal
        SYSCALL  (0x7f)
        cmpl    $-1, %eax               / error?
        jne     1f
        movl    $EINVAL, _errno
1:      ret

/ void __unwind (void)

        .align  2, 0x90

___unwind:
        movb    $0x10, %al              / unwind
        SYSCALL (0x7f)
        ret

/ int __read_kbd (int echo, int wait, int sig)

        .align  2, 0x90

___read_kbd:
        cmpl    $0, 3*4(%esp)           / sig
        jne     read_kbd_sig
        cmpl    $0, 2*4(%esp)           / wait
        jne     read_kbd_wait
        movb    $255, %dl
        SYSCALL(0x06)
        je      read_kbd_nothing
        movzbl  %al, %eax
read_kbd_echo:
        cmpl    $0, 1*4(%esp)           / echo
        je      read_kbd_ret
        pushl   %eax
        movb    %al, %dl
        SYSCALL(0x06)
        popl    %eax
read_kbd_ret:
        ret

read_kbd_wait:
        SYSCALL(0x07)
        movzbl  %al, %eax
        jmp     read_kbd_echo

read_kbd_sig:
        cmpl    $0, 2*4(%esp)           / wait
        jne     read_kbd_sig_wait
        SYSCALL(0x0b)
        cmpb    $0, %al
        je      read_kbd_nothing
read_kbd_sig_wait:
        cmpl    $0, 1*4(%esp)           / echo
        jne     read_kbd_sig_echo
        SYSCALL(0x08)
        movzbl  %al, %eax
        ret

read_kbd_sig_echo:
        SYSCALL(0x01)
        movzbl  %al, %eax
        ret

read_kbd_nothing:
        movl    $-1, %eax
        ret


/ int __ptrace (int request, int pid, int addr, int data)

        .align  2, 0x90

___ptrace:
        pushl   %ebx
        pushl   %edi
        movl    3*4(%esp), %ebx         / request
        movl    4*4(%esp), %edi         / pid
        movl    5*4(%esp), %edx         / addr
        movl    6*4(%esp), %ecx         / data
        movb    $8, %al                 / ptrace
        SYSCALL(0x7f)
        jecxz   1f
        movl    %ecx, _errno
1:      popl    %edi
        popl    %ebx
        ret


/ int __wait (int *term)
/
/ note: do not call with term == NULL!

        .align  2, 0x90

___wait:
        movb    $9, %al
        SYSCALL(0x7f)
        movl    1*4(%esp), %ecx
        movl    %edx, (%ecx)
        ret


/ char __getdrive (void)

        .align  2, 0x90

___getdrive:
        SYSCALL(0x19)
        addb    $0x41, %al
        movzbl  %al, %eax
        ret


/ void __cgets (char *buffer)

        .align  2, 0x90

___cgets:
        movl    1*4(%esp), %edx
        SYSCALL(0x0a)
        ret


/ int __memavail (void)

        .align  2, 0x90

___memavail:
        movb    $0x0b, %al
        SYSCALL(0x7f)
        ret


/ int __core (int handle)

        .align  2, 0x90

___core:
        pushl   %ebx
        movl    2*4(%esp), %ebx
        movb    $0x11, %al
        SYSCALL(0x7f)
        popl    %ebx
        jmp     sysret0


/ int __ioctl2 (int handle, int request, void *arg)

        .align  2, 0x90

___ioctl2:
        pushl   %ebx
        movl    2*4(%esp), %ebx         / handle
        movl    3*4(%esp), %ecx         / request
        movl    4*4(%esp), %edx         / arg
        movb    $0x14, %al              / ioctl2
        SYSCALL(0x7f)
        jecxz   1f
        movl    %ecx, _errno
1:      popl    %ebx
        ret


/ unsigned __alarm (unsigned sec)

        .align  2, 0x90

___alarm:
        movl    1*4(%esp), %edx
        movb    $0x15, %al
        SYSCALL(0x7f)
        ret


/ unsigned __sleep (unsigned sec)

        .align  2, 0x90

___sleep:
        movl    1*4(%esp), %edx
        movb    $0x17, %al
        SYSCALL(0x7f)
        ret

/ int __portaccess (unsigned first, unsigned last)

        .align  2, 0x90

___portaccess:
        movl    1*4(%esp), %ecx         / first
        movl    2*4(%esp), %edx         / last
        movb    $0x12, %al
        SYSCALL (0x7f)
        jmp     sysret0

/ void * __memaccess (unsigned first, unsigned last)

        .align  2, 0x90

___memaccess:
        movl    1*4(%esp), %ecx         / first
        movl    2*4(%esp), %edx         / last
        movb    $0x13, %al
        SYSCALL (0x7f)
        jnb     1f
        movl    %eax, _errno
        xorl    %eax, %eax              / NULL
1:      ret


/ int __ftruncate (int handle, long length)

        .align  2, 0x90

___ftruncate:
        pushl   %ebx
        movl    2*4(%esp), %ebx         / handle
        movl    3*4(%esp), %edx         / length
        movb    $0x18, %al
        SYSCALL(0x7f)
        popl    %ebx
        jmp     sysret0


/ int __fcntl (int handle, int request, int arg)

        .align  2, 0x90

___fcntl:
        pushl   %ebx
        movl    2*4(%esp), %ebx         / handle
        movl    3*4(%esp), %ecx         / request
        movl    4*4(%esp), %edx         / arg
        movb    $0x19, %al              / fcntl
        SYSCALL(0x7f)
        jecxz   1f
        movl    %ecx, _errno
1:      popl    %ebx
        ret


/ int __chdrive (char drive)

        .align  2, 0x90

___chdrive:
        movb    1*4(%esp), %dl          / drive
        subl    $0x41, %dl
        SYSCALL(0x0E)
        xorl    %eax, %eax
        ret


/ int __pipe (int *two_handles, int pipe_size)

        .align  2, 0x90

___pipe:
        movl    1*4(%esp), %edx         / two_handles
        movl    2*4(%esp), %ecx         / pipe_size
        movb    $0x1a, %al              / __pipe
        SYSCALL(0x7f)
        jecxz   1f
        movl    %ecx, _errno
1:      ret


/ int __fsync (int handle)

        .align  2, 0x90

___fsync:
        pushl   %ebx
        movl    2*4(%esp), %ebx         / handle
        movb    $0x1b, %al              / __fsync
        SYSCALL(0x7f)
        jecxz   1f
        movl    %ecx, _errno
1:      popl    %ebx
        ret

/ void __scrsize (int *dst)

        .align  2, 0x90

___scrsize:
        movl    1*4(%esp), %edx         / dst
        movb    $0x1d, %al              / __scrsize
        SYSCALL(0x7f)
        ret

/ void __select (struct _select *args)

        .align  2, 0x90

___select:
        movl    1*4(%esp), %edx         / args
        movb    $0x1e, %al              / __select
        SYSCALL(0x7f)
        jecxz   1f
        movl    %ecx, _errno
1:      ret


/ int __syserrno (void)

        .align  2, 0x90

___syserrno:
        movb    $0x1f, %al              / __syserrno
        SYSCALL(0x7f)
        ret
