/* sys/emx.h (emx/gcc) */

/* Must be included before any other head files */

#define FALSE 0
#define TRUE  1

extern const int _nfiles;
extern char ** _org_environ;

#define _SIZE_T_DEFINED
typedef unsigned long size_t;

struct _new_proc
    {
    unsigned long arg_off;
    unsigned long env_off;
    unsigned long fname_off;
    unsigned short arg_sel;
    unsigned short env_sel;
    unsigned short fname_sel;
    unsigned short arg_count;
    unsigned short arg_size;
    unsigned short env_count;
    unsigned short env_size;
    unsigned short mode;
    };

struct _ftd
    {
    unsigned int sec   : 5;
    unsigned int min   : 6;
    unsigned int hour  : 5;
    unsigned int day   : 5;
    unsigned int month : 4;
    unsigned int year  : 7;
    };

struct _dtd
    {
    unsigned char hsec;
    unsigned char sec;
    unsigned char min;
    unsigned char hour;
    unsigned char day;
    unsigned char month;
    unsigned short year;
    };

struct _find
    {
    char reserved[21];
    unsigned char attr;
    unsigned short time;
    unsigned short date;
    unsigned short size_lo;         /* split due to alignment problems      */
    unsigned short size_hi;
    char name[257];                 /* Big buffer for OS/2                  */
    };

struct _fd_set;
struct timeval;

struct _select
    {
    int nfds;
    struct _fd_set *readfds;
    struct _fd_set *writefds;
    struct _fd_set *exceptfds;
    struct timeval *timeout;
    };

extern struct _dtd _start_time;

#define _NFILES 40

/* Low-level i/o */

/*      O_ACCMODE   0x00000003 */
/*      O_NDELAY    0x00000004 */
/*      O_APPEND    0x00000008 */
/*      O_TEXT      0x00000010 */
#define F_EOF       0x00000020
#define F_TERMIO    0x00000040
#define F_DEV       0x00000080
/*      O_BINARY    0x00000100 */
/*      O_CREAT     0x00000200 */
/*      O_TRUNC     0x00000400 */
/*      O_EXCL      0x00000800 */
#define F_NPIPE     0x00001000

/* stdio */

/*      _IOREAD     0x00000001 */
/*      _IOWRT      0x00000002 */
/*      _IORW       0x00000004 */
/*      _IOEOF      0x00000008 */
/*      _IOERR      0x00000010 */
/*      _IOLBF      0x00000020 */
/*      _IONBF      0x00000040 */
#define _IOOPEN     0x00000080
#define _IOBUFMASK  0x00000700
#define _IOBUFNONE  0x00000000
#define _IOBUFUSER  0x00000100
#define _IOBUFCHAR  0x00000200
#define _IOBUFLIB   0x00000300
#define _IOBUFTMP   0x00000400
#define _IOTMP      0x00000800
#define _IOSTRING   0x00001000
#define _IOREREAD   0x00002000

/* argv[i][-1] contains some flag bits: */

#define _ARG_DQUOTE   0x01          /* Argument quoted (")                  */
#define _ARG_RESPONSE 0x02          /* Argument read from response file     */
#define _ARG_WILDCARD 0x04          /* Argument expanded from wildcard      */
#define _ARG_NONZERO  0x80          /* Always set, to avoid end of string   */

/* _uflags constants */

#define _UF_SIG_BENIGN 0x0001       /* Benign signal handlers               */

#if !defined (__IODATA)
extern int _files[];
extern int _lookahead[];
#endif

#if !defined (_EXIT_C)
extern void (*_atexit_v[32])(void);
extern int _atexit_n;
#endif

#define END_OF_HEAP 0xfffffffe      /* even! */

#define rover _malloc_rover
#define bottom _malloc_bottom
#define top _malloc_top

#if !defined (__MALLOC)
extern size_t *rover, *bottom, *top;
#endif

struct tm;
struct _stdio;

#define alloca __builtin_alloca

unsigned __alarm (unsigned sec);
void __cgets (char *buffer);
int __chdir (const char *name);
int __chmod (const char *name, int flag, int attr);
int __chdrive (char drive);
int __close (int handle);
int __core (int handle);
int __creat (const char *name, int attr);
int __dup (int handle);
int __dup2 (int handle1, int handle2);
int __fcntl (int handle, int request, int arg);
int __filetime (int handle, int flag, struct _ftd *date_time);
int __findfirst (const char *name, int attr, struct _find *fp);
int __findnext (struct _find *fp);
int __fsync (int handle);
void __ftime (struct _dtd *date_time);
int __ftruncate (int handle, long length);
int __getcwd (char *buffer, char drive);
char __getdrive (void);
int __getpid (void);
int __ioctl1 (int handle, int code);
int __ioctl2 (int handle, int request, int arg);
int __kill (int pid, int sig);
int __lseek (int handle, long offset, int origin);
void *__memaccess (unsigned first, unsigned last);
int __memavail (void);
int __mkdir (const char *name);
int __open (const char *name, int access);
int __pipe (int *two_handles, int pipe_size);
int __portaccess (unsigned first, unsigned last);
int __ptrace (int request, int pid, int addr, int data);
int __raise (int sig);
int __read (int handle, void *buf, size_t nbyte);
int __read_kbd (int echo, int wait, int sig);
int __remove (const char *name);
int __rename (const char *old_name, const char *new_name);
int __rmdir (const char *name);
void *__sbrk (int incr);
void __scrsize (int *dst);
int __select (struct _select *args);
void (*__signal (int sig, void (*handler)()))(int sig);
unsigned __sleep (unsigned sec);
int __spawnve (struct _new_proc *np);
int __swchar (int flag, int new);
int __syserrno (void);
int __uflags (int mask, int new);
long __ulimit (int cmd, long new_limit);
int __umask (int pmode);
void __unwind (void);
int __wait (int *status);
int __write (int handle, const void *buf, size_t nbyte);

void _cleanup (void);
int _day (int year, int month, int day);
void _endbuf (struct _stdio *stream);
void _fbuf (struct _stdio *stream);
struct _stdio *_fopen (struct _stdio *dst, const char *fname, const char *mode);
int _fxam (double x);
int _input (struct _stdio *stream, const char *format, char *arg_ptr);
int _mktime (struct tm *t);
struct _stdio *_newstream (void);
int _output (struct _stdio *stream, const char *format, char *arg_ptr);
void _tmpbuf (struct _stdio *stream);

#define nbuf(s) (((s)->flags & _IOBUFMASK) == _IOBUFNONE)
#define cbuf(s) (((s)->flags & _IOBUFMASK) == _IOBUFCHAR)
#define ubuf(s) (((s)->flags & _IOBUFMASK) == _IOBUFUSER)
#define lbuf(s) (((s)->flags & _IOBUFMASK) == _IOBUFLIB)
#define tbuf(s) (((s)->flags & _IOBUFMASK) == _IOBUFTMP)

#define bbuf(s) (ubuf (s) || lbuf (s) || tbuf (s))

/* Replace some bits in an lvalue */

#define SETBITS(dst,mask,new) ((dst) = ((dst) & ~(mask)) | ((new) & (mask)))

#define FX_P_NAN       1
#define FX_N_NAN       3
#define FX_P_NORMAL    4
#define FX_P_INFINITY  5
#define FX_N_NORMAL    6
#define FX_N_INFINITY  7
#define FX_P_ZERO      8
#define FX_P_EMPTY     9
#define FX_N_ZERO     10
#define FX_N_EMPTY    11
#define FX_P_DENORMAL 12
#define FX_N_DENORMAL 14

#define _A_NORMAL 0x00  /* No attributes */
#define _A_RDONLY 0x01  /* Read-only     */
#define _A_HIDDEN 0x02  /* Hidden        */
#define _A_SYSTEM 0x04  /* System        */
#define _A_VOLID  0x08  /* Volume label  */
#define _A_SUBDIR 0x10  /* Directory     */
#define _A_ARCH   0x20  /* Archive       */
