/* realloc.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdlib.h>

void *realloc (void *mem, size_t new_size)
    {
    void *p;
    size_t *block;
    size_t old_size;

    if (mem == NULL)
        return (malloc (new_size));
    if (new_size == 0)
        {
        free (mem);
        return (NULL);
        }
    block = mem;
    --block;
    old_size = (*block & ~1);
    *block = old_size;          /* in use */
    if (_expand (mem, new_size) != NULL)
        return (mem);
    p = malloc (new_size);
    if (p != NULL)
        {
        memcpy (p, mem, old_size);
        free (mem);
        }
    else
        _expand (mem, old_size);        /* shrink block to original size */
    return (p);
    }
