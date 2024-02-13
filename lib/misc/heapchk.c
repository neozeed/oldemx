/* heapchk.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>
#include <string.h>

static int dummy;

#define HEAP_NO_FILL 0xf7dc6a4e      /* illegal fill value */

int _heapchk (void)
    {
    return (_heapset (HEAP_NO_FILL));
    }

int _heapset (unsigned fill)
    {
    size_t *p, *last;
    size_t len, next;
    int met_rover;

    met_rover = 0;
    if (rover == NULL && bottom == NULL && top == NULL)
        return (_HEAPEMPTY);
    if (rover == NULL || bottom == NULL || top == NULL)
        return (_HEAPBADBEGIN);
    if ((size_t)bottom >= (size_t)top)
        return (_HEAPBADBEGIN);
    if (((size_t)bottom & 3) != 0 || ((size_t)top & 3) != 0)
        return (_HEAPBADBEGIN);
    if ((size_t)bottom <= (size_t)&dummy)
        return (_HEAPBADBEGIN);
    last = sbrk (0);
    if ((size_t)top >= (size_t)last)
        return (_HEAPBADEND);
    if (*top != END_OF_HEAP)
        return (_HEAPBADEND);
    p = bottom;
    while (p != top)
        {
        if (*p == END_OF_HEAP)
            return (_HEAPBADNODE);
        len = *p;
        if (len > 0x7fffffff)
            return (_HEAPBADNODE);
        next = (size_t)p + sizeof (size_t) + (len & ~1);
        if (next <= (size_t)p || next > (size_t)top)
            return (_HEAPBADNODE);
        if (fill != HEAP_NO_FILL && (len & 1))
            memset ((char *)p + sizeof (size_t), (int)fill, len & ~1);
        if (p == rover)
            ++met_rover;
        p = (size_t *)next;
        }
    if (met_rover != 1)
        return (_HEAPBADROVER);
    return (_HEAPOK);
    }
