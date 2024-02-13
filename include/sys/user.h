/* user.h (emx/gcc) */

#if !defined (_SYS_USER_H)
#define _SYS_USER_H

#define UMAGIC 0x10f

struct fpstate
    {
    unsigned long state[27];
    unsigned long status;
    };

struct user
    {
    unsigned short u_magic;
    unsigned short u_reserved1;
    unsigned long u_data_base;
    unsigned long u_data_end;
    unsigned long u_data_off;
    unsigned long u_heap_base;
    unsigned long u_heap_end;
    unsigned long u_heap_off;
    unsigned long u_heap_brk;
    unsigned long u_stack_base;
    unsigned long u_stack_end;
    unsigned long u_stack_off;
    unsigned long u_stack_low;
    int *u_ar0;
    char u_fpvalid;
    char u_reserved2[3];
    struct fpstate u_fpstate;
    unsigned long u_reserved3[23];
    unsigned long u_regs[19];
    };

#endif /* !defined (_SYS_USER_H) */
