/* dirent.h (emx/gcc) */

#if !defined (_DIRENT_H)
#define _DIRENT_H

#include <sys/dirent.h>

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
struct dirent *readdir (DIR *dirp);
void seekdir (DIR *dirp, long off);
long telldir (DIR *dirp);
void closedir (DIR *dirp);
void rewinddir (DIR *dirp);

#endif
