/* getuid.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */


unsigned int getuid (void)
    {
    return (0);                                                  /* root! */
    }


unsigned int geteuid (void)
    {
    return (0);
    }


unsigned int getgid (void)
    {
    return (0);
    }


unsigned int getegid (void)
    {
    return (0);
    }


char *getlogin (void)
    {
    return ("root");
    }
