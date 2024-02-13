/* free.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdlib.h>

void free (void *mem)
    {
    if (mem != NULL)
        {
        ((size_t *)mem)[-1] |= 1;
        }
    }
