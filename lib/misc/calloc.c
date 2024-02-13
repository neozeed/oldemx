/* calloc.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdlib.h>
#include <string.h>

void *calloc (size_t elements, size_t size)
    {
    size_t bytes;
    void *p;

    bytes = elements * size;
    if (size != 0 && bytes / size != elements)     /* Check for overflow */
        return (NULL);
    p = malloc (bytes);
    if (p != NULL)
        (void)memset (p, 0, bytes);
    return (p);
    }
