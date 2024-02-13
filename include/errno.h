/* errno.h (emx/gcc) */

#if !defined (_ERRNO_H)
#define _ERRNO_H

extern int errno;

#define ENOENT      2   /* No such file or directory            */
#define ESRCH       3   /* No such process                      */
#define EINTR       4   /* Interrupted system call              */
#define EIO         5   /* I/O error                            */
#define E2BIG       7   /* Arguments or environment too big     */
#define ENOEXEC     8   /* Invalid executable file format       */
#define EBADF       9   /* Bad file number                      */
#define ECHILD      10  /* No child processes                   */
#define EAGAIN      11  /* No more processes                    */
#define ENOMEM      12  /* Not enough memory                    */
#define EACCES      13  /* Permission denied                    */
#define EEXIST      17  /* File exists                          */
#define EXDEV       18  /* Cross-device link                    */
#define EINVAL      22  /* Invalid argument                     */
#define EMFILE      24  /* Too many open files                  */
#define ENOSPC      28  /* Disk full                            */
#define EPIPE       32  /* Broken pipe                          */
#define ERANGE      34  /* Result too large                     */
#define EMSDOS      37  /* Not supported under MS-DOS           */

#endif /* !defined (_ERRNO_H) */
