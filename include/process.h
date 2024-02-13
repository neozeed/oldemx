/* process.h (emx/gcc) */

#if !defined (_PROCESS_H)
#define _PROCESS_H

#if !defined (P_WAIT)
#define P_WAIT    0
#define P_NOWAIT  1
#define P_OVERLAY 2
#define P_DEBUG   3
#define P_SESSION 4
#define P_DETACH  5

#define P_DEFAULT    0x0000
#define P_MINIMIZE   0x0100
#define P_MAXIMIZE   0x0200
#define P_FULLSCREEN 0x0300
#define P_WINDOWED   0x0400

#define P_FOREGROUND 0x0000
#define P_BACKGROUND 0x1000

#define P_NOCLOSE    0x2000

#endif

void abort (void);
int atexit (void (*func)(void));
int execl (const char *name, const char *arg0, ...);
int execle (const char *name, const char *arg0, ...);
int execlp (const char *name, const char *arg0, ...);
int execlpe (const char *name, const char *arg0, ...);
int execv (const char *name, const char * const *argv);
int execve (const char *name, const char * const *argv, const char * const *envp);
int execvp (const char *name, const char * const *argv);
int execvpe(const char *name, const char * const *argv, const char * const *envp);
void volatile exit (int ret);
void volatile _exit (int ret);
int getpid (void);
int spawnl (int mode, const char *name, const char *arg0, ...);
int spawnle (int mode, const char *name, const char *arg0, ...);
int spawnlp (int mode, const char *name, const char *arg0, ...);
int spawnlpe (int mode, const char *name, const char *arg0, ...);
int spawnv (int mode, const char *name, const char * const *argv);
int spawnve (int mode, const char *name, const char * const *argv, const char * const *envp);
int spawnvp (int mode, const char *name, const char * const *argv);
int spawnvpe (int mode, const char *name, const char * const *argv, const char * const *envp);
int system (const char *name);
int wait (int *term);

#endif /* !defined (_PROCESS_H) */
