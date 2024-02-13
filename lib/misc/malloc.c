/* malloc.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#define __MALLOC

#include <sys/emx.h>
#include <stdlib.h>

/* to do: take size of last free block into account, if no used block */
/*        follows and if sbrk() must be called.                       */

/* Bug: sbrk/brk must not be called by user program to change data    */
/*      segment size (very complicated to fix). malloc returns NULL   */
/*      if it thinks the data segment size has been changed.          */

size_t *rover = NULL;
size_t *bottom = NULL;
size_t *top = NULL;


static void *_malloc1 (size_t size);

void *malloc (size_t size)
    {
    void *p;
    size_t n;

    if (size >= (size_t)(-16))
        return (NULL);
    if (rover == NULL)
        {
        n = (size_t)sbrk (0);
        if ((n & 3) != 0)
            sbrk (4 - (n & 3));
        p = sbrk (2 * sizeof (size_t));
        if (p == (void *)(-1) || ((size_t)p & 3) != 0)
            return (NULL);
        bottom = rover = p;
        top = bottom+1;
        *bottom = 1;                    /* length = 0, free */
        *top = END_OF_HEAP;             /* End of heap      */
        }
    return (_malloc1 (size));
    }


/* pass 1: search from rover to end of heap   */
/* pass 2: search from start of heap to rover */
/* pass 3: search from rover to end of heap (after growing heap) */

static void *_malloc1 (size_t size)
    {
    size_t *block, *base;
    void *p;
    size_t len, n;
    int pass;

    if (size >= (size_t)(-16))
        return (NULL);
    size = (size+1) & ~1;     /* Make size even, bit 0 used as flag */
                              /* Optionally, align to DWORD for performance */
    pass = 1;
restart:
    block = base = rover;
in_use:
    if (*block & 1)
        goto free_start;
not_free:
    if (pass == 2 && (size_t)block > (size_t)rover)
        {
        block = top;
        goto not_found;
        }
    if (*block == END_OF_HEAP)
        {
        if (block != top)
            return (NULL);
        if (pass >= 2)
            goto not_found;
        ++pass; block = bottom;
        goto in_use;
        }
    block = (size_t *)((char *)block + sizeof (size_t) + *block);
    goto in_use;

free_start:
    base = block;
    len = *base & ~1;
free_loop:
    if (len >= size)
        goto found;
    block = (size_t *)((char *)base + sizeof (size_t) + len);
    if (!(*block & 1))
        goto not_free;
    len += sizeof (size_t) + (*block & ~1);
    *base = len | 1;
    goto free_loop;

found:
    if (len - size > sizeof (size_t))
        {
        *base = size;                       /* even, ie, in use */
        block = (size_t *)((char *)base + sizeof (size_t) + size);
        *block = (len - size - sizeof (size_t)) | 1;
        }
    else
        *base &= ~1;                       /* in use! */
    rover = base;
    return ((void *)((char *)base + sizeof (size_t)));

not_found:
    n = (size + sizeof (size_t) + 0xfff) & ~0xfff;
    if (n < 65536) n = 65536;       /* memory is cheap, searching expensive */
    p = sbrk (n);
    if (p == (void *)(-1))
        return (NULL);
    if (p != top+1)
        return (NULL);
    *top = (n - sizeof (size_t)) | 1;
    top = (size_t *)((char *)top + n);
    *top = END_OF_HEAP;
    pass = 3; rover = base;
    goto restart;
    }
