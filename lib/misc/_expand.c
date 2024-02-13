/* _expand.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>

void *_expand (void *mem, size_t size)
    {
    size_t in_use, len, xlen;
    size_t *base, *block;
    void *p;

    if (size > (size_t)(-16))
        return (NULL);
    size = (size+1) & ~1;
    base = mem;
    --base;
    in_use = *base;
restart:
    *base &= ~1;            /* temporarily in-use */
    len = *base;
    for (;;)
        {
        block = (size_t *)((char *)base + sizeof (size_t) + len);
        if (block == rover)
            rover = base;       /* avoid invalid rover */
        xlen = *block;
        if (!(xlen & 1))        /* block in use? */
            break;              /* yes -> end of contiguous area */
        len += sizeof (size_t) + (xlen & ~1);
        }
    if (len >= size)
        goto success;
    *base = (len & ~1) | (in_use & 1);
    if (*block != END_OF_HEAP)
        return (NULL);
    xlen = (size-len + sizeof (size_t) + 0xfff) & ~0xfff;
    p = sbrk (xlen);
    if (p == (void *)(-1))
        return (NULL);
    if (p != top+1)
        return (NULL);
    *top = (xlen - sizeof (size_t)) | 1;
    top = (size_t *)((char *)top + xlen);
    *top = END_OF_HEAP;
    goto restart;

success:
    if (len - size > sizeof (size_t))
        {
        block = (size_t *)((char *)base + sizeof (size_t) + size);
        *block = (len - size - sizeof (size_t)) | 1;
        len = size;
        }
    *base = (len & ~1) | (in_use & 1);
    ++base;
    return (base);
    }
