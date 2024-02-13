/* setjmp.h (emx/gcc) */

#if !defined (_JMPBUF_DEFINED)
#define _JMPBUF_DEFINED

typedef int jmp_buf[12];
#endif

int setjmp (jmp_buf here);
void volatile longjmp (jmp_buf there, int n);
