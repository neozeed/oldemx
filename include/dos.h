/* dos.h (emx/gcc) */

#if !defined (_REGS_DEFINED)
#define _REGS_DEFINED

struct _dwordregs
    {
    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;
    unsigned int esi;
    unsigned int edi;
    unsigned int eflags;
    };

struct _wordregs
    {
    unsigned short ax, h_ax;
    unsigned short bx, h_bx;
    unsigned short cx, h_cx;
    unsigned short dx, h_dx;
    unsigned short si, h_si;
    unsigned short di, h_di;
    unsigned short flags, h_flags;
    };

struct _byteregs
    {
    unsigned char al, ah, h_al, h_ah;
    unsigned char bl, bh, h_bl, h_bh;
    unsigned char cl, ch, h_cl, h_ch;
    unsigned char dl, dh, h_dl, h_dh;
    };

union REGS {
    struct _dwordregs e;
    struct _wordregs x;
    struct _byteregs h;
    };

struct SREGS
    {
    unsigned int cs;
    unsigned int ds;
    unsigned int es;
    unsigned int fs;
    unsigned int gs;
    unsigned int ss;
    };

#endif

int _int86 (int int_num, union REGS *inp_regs, union REGS *out_regs);
void _segread (struct SREGS *seg_regs);

int _portaccess (unsigned first, unsigned last);
void *_memaccess (unsigned first, unsigned last);
