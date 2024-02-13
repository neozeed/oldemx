/* sys/signal.h (emx/gcc) */

#if !defined (_SYS_SIGNAL_H)
#define _SYS_SIGNAL_H

typedef int sig_atomic_t;

#define SIGTY void

#define SIGHUP    1 /* Hangup */
#define SIGINT    2 /* Interrupt (Ctrl-C) */
#define SIGQUIT   3 /* Quit */
#define SIGILL    4 /* Illegal instruction */
#define SIGTRAP   5 /* Single step (debugging) */
#define SIGABRT   6 /* abort () */
#define SIGEMT    7 /* ??? */
#define SIGFPE    8 /* Floating point */
#define SIGKILL   9 /* Kill process */
#define SIGBUS   10 /* ??? */
#define SIGSEGV  11 /* Segmentation fault */
#define SIGSYS   12 /* Invalid argument to system call */
#define SIGPIPE  13 /* Broken pipe */
#define SIGALRM  14 /* Alarm */
#define SIGTERM  15 /* Termination, process killed */
#define SIGCLD   18 /* Death of a child process */
#define SIGBREAK 21 /* Break (Ctrl-Break) */

#define NSIG 22

#define SIG_DFL ((void (*)(int))0)
#define SIG_IGN ((void (*)(int))1)
#define SIG_ACK ((void (*)(int))4)
#define SIG_ERR ((void (*)(int))-1)

void (*signal (int sig, void (*handler)()))(int sig);
int raise (int sig);
int kill (int pid, int sig);

#endif /* !defined (_SYS_SIGNAL_H) */
