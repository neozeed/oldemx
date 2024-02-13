/* timetest.c */

#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char *argv[])
    {
    time_t t;
    time_t zero;
    int i;
    struct stat s;

    for (i = 1; i < argc; ++i)
        {
        if (stat (argv[i], &s) != 0)
            perror (argv[i]);
        else
            {
            printf ("%s:\n", argv[i]);
            printf ("  dev=%d ino=%d mode=%d nlink=%d\n",
                    (int)s.st_dev, (int)s.st_ino, (int)s.st_mode, (int)s.st_nlink);
            printf ("  uid=%d gid=%d rdev=%d size=%d\n",
                    (int)s.st_uid, (int)s.st_gid, (int)s.st_rdev, (int)s.st_size);
            printf ("  atime=%s", ctime (&s.st_atime));
            printf ("  mtime=%s", ctime (&s.st_mtime));
            printf ("  ctime=%s", ctime (&s.st_ctime));
            }
        }
    zero = 0;
    time (&t);
    printf ("time = %ld\n", (long)t);
    printf ("clock = %ld\n", (long)clock ());
    printf ("ctime(0) = %s", ctime (&zero));
    printf ("ctime = %s", ctime (&t));
    return (0);
    }
