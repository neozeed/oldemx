/* fcntl.h (emx/gcc) */

#if !defined (O_RDONLY)
#define O_RDONLY        0x00
#define O_WRONLY        0x01
#define O_RDWR          0x02
#define O_APPEND        0x08
#define O_TEXT          0x10
#define O_BINARY        0x20
#define O_CREAT         0x100
#define O_TRUNC         0x200
#define O_EXCL          0x400
#endif

#if !defined (F_OK)
#define F_OK 0
#define X_OK 1
#define W_OK 2
#define R_OK 4
#endif
