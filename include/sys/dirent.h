/* sys/dirent.h (emx/gcc) */

#if !defined (_SYS_DIRENT_H)
#define _SYS_DIRENT_H

#if !defined (MAXNAMLEN)
#define MAXNAMLEN  260
#endif

#if !defined (MAXPATHLEN)
#define MAXPATHLEN 260
#endif

#if !defined (A_RONLY)
#define A_RONLY   0x01
#define A_HIDDEN  0x02
#define A_SYSTEM  0x04
#define A_LABEL   0x08
#define A_DIR     0x10
#define A_ARCHIVE 0x20
#endif

struct dirent
    {
    ino_t d_ino;                    /* Almost not used */
    int d_reclen;                   /* Almost not used */
    int d_namlen;                   /* Length of d_name */
    char d_name[MAXNAMLEN + 1];     /* File name, 0 terminated */

    long d_size;                    /* File size (bytes) */
    unsigned short d_mode;          /* DOS file attributes */
    unsigned short d_time;          /* DOS file modification time */
    unsigned short d_date;          /* DOS file modification date */
    };

#endif /* !defined (SYS_DIRENT_H) */
