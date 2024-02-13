/* _fngetdr.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <stdlib.h>

char _fngetdrive (const char *src)
    {
    if (src[0] >= 'A' && src[0] <= 'Z' && src[1] == ':')
        return (src[0]);
    else if (src[0] >= 'a' && src[0] <= 'z' && src[1] == ':')
        return (src[0]-'a'+'A');
    else
        return (0);
    }
