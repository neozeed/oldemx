/ syscalls.s (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes

#define SYSCALL(x) movb $x,%ah;call __syscall

#define EINVAL 22

        .globl  __open, __close, __creat, __ioctl1, __ioctl2
        .globl  __write, __read, __lseek, __chmod
        .globl  __remove, __rename, __ftime, __time
        .globl  __ulimit3, __chdir, __mkdir, __rmdir
        .globl  __findfirst, __findnext, __uflags, __swchar
        .globl  _dup, __getcwd, __spawnve, __wait
        .globl  _sbrk, _umask, _getpid, _signal, _raise, _kill
        .globl  _ptrace, __unwind, __read_kbd, __alarm, __sleep
        .globl  _ll_getdrive, __cgets, __memavail, __core
        .globl  __portaccess, __memaccess


/ _open (char *path, int access)

__open:
        movb    2*4(%esp), %al          / access
        movl    1*4(%esp), %edx         / path
        SYSCALL(0x3d)
        jmp     dosreteax


/ _creat (char *path, int attr)

__creat:
        movl    2*4(%esp), %ecx         / attr
        movl    1*4(%esp), %edx         / path
        SYSCALL(0x3c)
        jmp     dosreteax


/ _close (int handle)

__close:
        pushl   %ebx
        movl    2*4(%esp), %ebx         / handle
        SYSCALL(0x3e)
        popl    %ebx
        jmp     dosret0


/ _write (int handle, void *buf, size_t nbyte)

        .align  2

__write:
        pushl   %ebx
        movl    4*4(%esp), %ecx         / nbyte
        movl    3*4(%esp), %edx         / buf
        movl    2*4(%esp), %ebx         / handle
        SYSCALL(0x40)
        popl    %ebx
dosreteax:
        jnb     dosreteax1
        movl    %eax, _errno
        movl    $-1, %eax
dosreteax1:
        ret


/ _read (int handle, void *buf, size_t nbyte)

        .align  2

__read:
        pushl   %ebx
        movl    4*4(%esp), %ecx         / nbyte
        movl    3*4(%esp), %edx         / buf
        movl    2*4(%esp), %ebx         / handle
        SYSCALL(0x3f)
        popl    %ebx
        jmp     dosreteax


/ _lseek (int handle, long offset, int origin)

        .align  2

__lseek:
        pushl   %ebx
        movb    4*4(%esp), %al          / origin
        movl    3*4(%esp), %edx         / offset
        movl    2*4(%esp), %ebx         / handle
        SYSCALL(0x42)
        popl    %ebx
        jmp     dosreteax


/ _ioctl1 (int handle, int code)

__ioctl1:
        pushl   %ebx
        movb    3*4(%esp), %al          / code
        movl    2*4(%esp), %ebx         / handle
        SYSCALL(0x44)
        popl    %ebx
dosretdx:
        jb      dosretdx1
        movzwl  %dx, %eax
        ret
dosretdx1:
        movl    %eax, _errno
        movl    $-1, %eax
        ret


/ int _chmod (char *name, int flag, int attr)

__chmod:
        movl    1*4(%esp), %edx         / name
        movb    2*4(%esp), %al          / flag
        movl    3*4(%esp), %ecx         / attr
        SYSCALL(0x43)
        jb      dosretcx1
        movzwl  %cx, %eax
        ret
dosretcx1:
        movl    %eax, _errno
        movl    $-1, %eax
        ret


/ int _remove (const char *name)

__remove:
        movl    1*4(%esp), %edx         / name
        SYSCALL(0x41)
        jmp     dosret0

/ int _rename (const char *old_name, const char *new_name)

__rename:
        pushl   %edi
        movl    2*4(%esp), %edx         / old_name
        movl    3*4(%esp), %edi         / new_name
        SYSCALL(0x56)
        popl    %edi
        jmp     dosret0


/ int _ftime (int handle, int flag, struct _ftd *date_time)

__ftime:
        pushl   %ebx
        movl    4*4(%esp), %ebx         / date_time
        movw    0(%ebx), %cx
        movw    2(%ebx), %dx
        movb    3*4(%esp), %al          / flag
        movl    2*4(%esp), %ebx         / handle
        SYSCALL(0x57)
        jnb     ftime1
        movl    %eax, _errno
        movl    $-1, %eax
        jmp     ftime2
ftime1: xorl    %eax, %eax
        movl    4*4(%esp), %ebx         / date_time
        movw    %cx, 0(%ebx)
        movw    %dx, 2(%ebx)
ftime2: popl    %ebx
        ret


/ void _time (struct _dtd *time_date)

__time:
        pushl   %ebx
        movl    2*4(%esp), %ebx
time1:  SYSCALL(0x2a)                   / Get date
        movb    %dl, 3(%ebx)            / day
        movb    %dh, 4(%ebx)            / month
        movw    %cx, 6(%ebx)            / year
        SYSCALL(0x2c)                   / Get time
        movb    %dh, 0(%ebx)            / sec
        movb    %cl, 1(%ebx)            / min
        movb    %ch, 2(%ebx)            / hour
/ Read the date again to avoid a problem at midnight
        SYSCALL(0x2a)                   / Get date
        cmpb    %dl, 3(%ebx)            / day
        jne     time1
        cmpb    %dh, 4(%ebx)            / month
        jne     time1
        cmpw    %cx, 6(%ebx)            / year
        jne     time1
        popl    %ebx
        ret


/ int _chdir (const char *name)

__chdir:
        movl    1*4(%esp), %edx
        SYSCALL(0x3b)
dosret0:jb      dosret1
        xorl    %eax, %eax
        ret
dosret1:movl    %eax, _errno
        movl    $-1, %eax
        ret


/ int _mkdir (const char *name)

__mkdir:
        movl    1*4(%esp), %edx
        SYSCALL(0x39)
        jmp     dosret0


/ int _rmdir (const char *name)

__rmdir:
        movl    1*4(%esp), %edx
        SYSCALL(0x3a)
        jmp     dosret0


/ int dup (int handle)

_dup:
        pushl   %ebx
        movl    2*4(%esp), %ebx         / handle
        SYSCALL(0x45)
        popl    %ebx
        jmp     dosreteax


/ int _getcwd (char *buffer, int drive)

__getcwd:
        pushl   %esi
        movl    2*4(%esp), %esi         / buffer
        movb    3*4(%esp), %dl          / drive
        SYSCALL(0x47)
        popl    %esi
        jmp     dosret0
        

/ int _findfirst (const char *name, int attr, struct _find *fp)

__findfirst:
        pushl   %esi
        movl    2*4(%esp), %edx
        movl    3*4(%esp), %ecx
        movl    4*4(%esp), %esi
        SYSCALL(0x4e)
        popl    %esi
        jmp     dosret0


/ int _findnext (struct _find *fp)

__findnext:
        pushl   %esi
        movl    2*4(%esp), %esi
        SYSCALL(0x4f)
        popl    %esi
        jmp     dosret0


/ long _ulimit3 (void)
/ = ulimit (3, 0)

__ulimit3:
        movb    $2, %al
        SYSCALL(0x7f)
        ret


/ int umask (int pmode)

_umask:
        movl    1*4(%esp), %edx         / pmode
        movb    $4, %al                 / umask
        SYSCALL(0x7f)
        ret


/ int _uflags (int mask, int new)

__uflags:
        movl    1*4(%esp), %ecx         / mask
        movl    2*4(%esp), %edx         / new
        movb    $15, %al                / uflags
        SYSCALL(0x7f)
        ret

/ int _swchar (int flag, int new)

__swchar:
        movb    1*4(%esp), %al          / flag
        movb    2*4(%esp), %dl          / new
        SYSCALL(0x37)
        movzbl  %al, %eax
        movb    %dl, %ah
        ret

/ void *sbrk (int incr)

        .align  2

_sbrk:
        movl    1*4(%esp), %edx
        movb    $0, %al
        SYSCALL(0x7f)
        ret


/ int getpid (void)

_getpid:
        movb    $5, %al
        SYSCALL(0x7f)
        ret
        

/ int _spawnve (struct _new_proc *np)

__spawnve:
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


/ int raise (int sig)

_raise: movl    1*4(%esp), %ecx         / sig
        movb    $14, %al                / raise
        SYSCALL(0x7f)
        ret


/ int kill (int pid, int sig)

_kill:  movl    1*4(%esp), %edx         / pid
        movl    2*4(%esp), %ecx         / sig
        movb    $0x0d, %al              / kill
        SYSCALL(0x7f)
        ret


/ void (*signal (int sig, void (*handler)()))(int sig)

_signal:
        movl    1*4(%esp), %ecx         / sig
        movl    2*4(%esp), %edx         / handler
        movb    $0x0c, %al              / signal
        SYSCALL  (0x7f)
        cmpl    $-1, %eax               / error?
        jne     1f
        movl    $EINVAL, _errno
1:      ret

/ void _unwind (void)

__unwind:
        movb    $0x10, %al              / _unwind
        SYSCALL (0x7f)
        ret

/ int _read_kbd (int echo, int wait, int sig)

__read_kbd:
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


/ int ptrace (int request, int pid, int addr, int data)

_ptrace:
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


/ int _wait (int *term)
/
/ note: do not call with term == NULL!

__wait:
        movb    $9, %al
        SYSCALL(0x7f)
        movl    1*4(%esp), %ecx
        movl    %edx, (%ecx)
        ret


/ char ll_getdrive (void)

_ll_getdrive:
        SYSCALL(0x19)
        addb    $0x41, %al
        movzbl  %al, %eax
        ret


/ void _cgets (char *buffer)

__cgets:
        movl    1*4(%esp), %edx
        SYSCALL(0x0a)
        ret


/ int _memavail (void)

        .align  2

__memavail:
        movb    $0x0b, %al
        SYSCALL(0x7f)
        ret


/ int _core (int handle)

        .align  2

__core:
        pushl   %ebx
        movl    2*4(%esp), %ebx
        movb    $0x11, %al
        SYSCALL(0x7f)
        popl    %ebx
        jmp     dosret0


/ int _ioctl2 (int handle, int request, void *arg)

__ioctl2:
        pushl   %ebx
        movl    2*4(%esp), %ebx         / handle
        movl    3*4(%esp), %ecx         / request
        movl    4*4(%esp), %edx         / arg
        movb    $0x14, %al              / _ioctl2
        SYSCALL(0x7f)
        jecxz   1f
        movl    %ecx, _errno
1:      popl    %ebx
        ret


/ unsigned _alarm (unsigned sec)

        .align  2

__alarm:
        movl    1*4(%esp), %edx
        movb    $0x15, %al
        SYSCALL(0x7f)
        ret


/ unsigned _sleep (unsigned sec)

        .align  2

__sleep:
        movl    1*4(%esp), %edx
        movb    $0x17, %al
        SYSCALL(0x7f)
        ret

/ int _portaccess (unsigned first, unsigned last)

        .align  2

__portaccess:
        movl    1*4(%esp), %ecx         / first
        movl    2*4(%esp), %edx         / last
        movb    $0x12, %al
        SYSCALL (0x7f)
        jmp     dosret0

/ void * _memaccess (unsigned first, unsigned last)

        .align  2

__memaccess:
        movl    1*4(%esp), %ecx         / first
        movl    2*4(%esp), %edx         / last
        movb    $0x13, %al
        SYSCALL (0x7f)
        jnb     1f
        movl    %eax, _errno
        xorl    %eax, %eax              / NULL
1:      ret
