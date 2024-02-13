/* pwd.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdio.h>
#include <pwd.h>


struct passwd *getpwent (void)
    {
    return (NULL);                           /* End of /etc/passwd reached */
    }


struct passwd *getpwuid (int uid)
    {
    return (NULL);                           /* End of /etc/passwd reached */
    }


struct passwd *getpwnam (char *name)
    {
    return (NULL);                           /* End of /etc/passwd reached */
    }


void setpwent (void)
    {
    }


void endpwent (void)
    {
    }
