/* unistd.h (emx/gcc) */

#if !defined (_UNISTD_H)
#define _UNISTD_H

#if !defined (NULL)
#define NULL ((void *)0)
#endif

#if !defined (STDIN_FILENO)
#define STDIN_FILENO    0
#define STDOUT_FILENO   1
#define STDERR_FILENO   2
#endif

#if !defined (F_OK)
#define F_OK 0
#define X_OK 1
#define W_OK 2
#define R_OK 4
#endif

#if !defined (SEEK_SET)
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif

#endif /* !defined (_UNISTD_H) */
