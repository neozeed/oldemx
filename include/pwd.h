/* pwd.h (emx/gcc) */

#if !defined (__PWD_H)

#define __PWD_H

struct passwd
    {
    char *pw_name;
    char *pw_passwd;
    int  pw_uid;
    int  pw_gid;
    char *pw_age;
    char *pw_comment;
    char *pw_gecos;
    char *pw_dir;
    char *pw_shell;
    };

struct passwd *getpwent (void);
struct passwd *getpwuid (int uid);
struct passwd *getpwnam (char *name);
void setpwent (void);
void endpwent (void);

#endif
