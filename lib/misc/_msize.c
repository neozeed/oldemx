/* _msize.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdlib.h>

size_t _msize (const void *mem)
    {
    return (*(size_t *)mem & ~1);
    }
