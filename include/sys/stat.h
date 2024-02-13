/* sys/stat.h (emx/gcc) */

#if !defined (_SYS_STAT_H)
#define _SYS_STAT_H

#if !defined (_TIME_T_DEFINED)
#define _TIME_T_DEFINED
typedef long time_t;
#endif

#if !defined (_STAT_DEFINED)
#define _STAT_DEFINED
struct stat
    {
    dev_t st_dev;
    ino_t st_ino;
    unsigned short st_mode;
    short st_nlink;
    short st_uid;
    short st_gid;
    dev_t st_rdev;
    off_t st_size;
    time_t st_atime;
    time_t st_mtime;
    time_t st_ctime;
    };
#endif

#if !defined (S_IREAD)
#define S_IREAD  0400     /* Owner: read */
#define S_IWRITE 0200     /* Owner: write */
#define S_IEXEC  0100     /* Owner: exec */

#define S_IFMT   0160000  /* Mask for file type */
#define S_IFCHR  0020000  /* Character device */
#define S_IFDIR  0040000  /* Directory */
#define S_IFREG  0100000  /* Regular file */
#endif

int fstat (int handle, struct stat *buffer);
int stat (const char *name, struct stat *buffer);

#endif /* !defined (SYS_STAT_H) */
