/* sys/dir.h (emx/gcc) */

#if !defined (_DIR_H)
#define _DIR_H

#if !defined (MAXNAMLEN)
#define MAXNAMLEN  65
#endif

#if !defined (MAXPATHLEN)
#define MAXPATHLEN 65
#endif

#if !defined (A_RONLY)
#define A_RONLY   0x01
#define A_HIDDEN  0x02
#define A_SYSTEM  0x04
#define A_LABEL   0x08
#define A_DIR     0x10
#define A_ARCHIVE 0x20
#endif

struct direct
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

struct _dircontents
    {
    char *_d_entry;
    long _d_size;
    unsigned short _d_mode;
    unsigned short _d_time;
    unsigned short _d_date;
    struct _dircontents *_d_next;
    };

struct _dirdesc
    {
    int  dd_id;
    long dd_loc;
    struct _dircontents *dd_contents;
    struct _dircontents *dd_cp;
    };

typedef struct _dirdesc DIR;

DIR *opendir (const char *name);
struct direct *readdir (DIR *dirp);
void seekdir (DIR *dirp, long off);
long telldir (DIR *dirp);
void closedir (DIR *dirp);
void rewinddir (DIR *dirp);

#endif
