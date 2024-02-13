/* io.h (emx/gcc) */

#if !defined (_SIZE_T)
#define _SIZE_T
typedef unsigned int size_t;
#endif

#if !defined (SEEK_SET)
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif

static struct stat *__keep_the_compiler_happy_2__ (void); /* use struct stat */

int access (const char *name, int mode);
int chmod (const char *name, int pmode);
int chsize (int handle, long size);
int close (int handle);
int creat (const char *name, int pmode);
int dup (int handle);
int dup2 (int handle1, int handle2);
int eof (int handle);
long filelength (int handle);
int fstat (int handle, struct stat *buffer);
int fsync (int handle);
int ftruncate (int handle, int length);
int ioctl (int handle, int request, ...);
int isatty (int handle);
long lseek (int handle, long offset, int origin);
char *mktemp (char *template);
int open (const char *name, int oflag, ...);
int read (int handle, void *buf, size_t nbyte);
int remove (const char *name);
int rename (const char *old_name, const char *new_name);
int setmode (int handle, int mode);
int sopen (const char *name, int oflag, int shflag, ...);
int stat (const char *name, struct stat *buffer);
long tell (int handle);
int truncate (char *name, int length);
int umask (int pmode);
int unlink (const char *name);
int write (int handle, const void *buf, size_t nbyte);

int _seek_hdr (int handle);
