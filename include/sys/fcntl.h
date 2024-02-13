/* sys/fcntl.h (emx/gcc) */

#if !defined (_SYS_FCNTL_H)
#define _SYS_FCNTL_H

/* Don't forget to update /emx/source/termio.inc when changing this! */

#if !defined (O_RDONLY)
#define O_ACCMODE       0x03    /* mask */
#define O_RDONLY        0x00
#define O_WRONLY        0x01
#define O_RDWR          0x02
#define O_NDELAY        0x04
#define O_APPEND        0x08
#define O_TEXT          0x10

#define O_NONBLOCK      O_NDELAY

#define O_BINARY        0x100
#define O_CREAT         0x200
#define O_TRUNC         0x400
#define O_EXCL          0x800

#endif

#if !defined (F_OK)
#define F_OK 0
#define X_OK 1
#define W_OK 2
#define R_OK 4
#endif

#if !defined (F_GETFL)
#define F_GETFL     1
#define F_SETFL     2
#define F_GETFD     3
#define F_SETFD     4
#endif

int fcntl (int handle, int request, int arg);

#endif /* !defined (_SYS_FCNTL_H) */
