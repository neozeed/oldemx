/* sys/signal.h (emx/gcc) */

#if !defined (__SIGNAL)

typedef int sig_atomic_t;

#define __SIGNAL

#define SIGTY void

#define SIGHUP    1 /* Hangup */
#define SIGINT    2 /* Interrupt (Ctrl-C) */
#define SIGQUIT   3 /* Quit */
#define SIGILL    4 /* Illegal instruction */
#define SIGTRAP   5 /* Single step (debugging) */
#define SIGABRT   6 /* abort () */
#define SIGBREAK  7 /* Break (Ctrl-Break) */
#define SIGFPE    8 /* Floating point */
#define SIGKILL   9 /* Kill process */
#define SIGSEGV  11 /* Segmentation fault */
#define SIGSYS   12 /* Invalid argument to system call */
#define SIGPIPE  13 /* Broken pipe */
#define SIGALRM  14 /* Alarm */
#define SIGTERM  15 /* Termination, process killed */

#define NSIG 16

#define SIG_DFL ((void (*)(int))0)
#define SIG_IGN ((void (*)(int))1)
#define SIG_ACK ((void (*)(int))4)
#define SIG_ERR ((void (*)(int))-1)

void (*signal (int sig, void (*handler)()))(int sig);
int raise (int sig);
int kill (int pid, int sig);

#endif
