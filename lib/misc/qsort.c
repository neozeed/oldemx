/* qsort.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdlib.h>

static size_t qs_width;
static int (*qs_compare)(const void *x1, const void *x2);

static void memswap (void *p1, void *p2, size_t size);
static void qsort1 (char *l, char *r);

void qsort (void *base, size_t num, size_t width,
            int (*compare)(const void *x1, const void *x2))
    {
    if (width > 0 && num > 1 && base != NULL)
        {
        qs_width = width; qs_compare = compare;
        qsort1 ((char *)base, (char *)base+(num-1)*width);
        }
    }


static void qsort1 (char *l, char *r)
    {
    char *i, *j, *x;

redo:
    i = l; j = r;
    x = l + qs_width * (((r-l) / qs_width) >> 1);
    do  {
        while (qs_compare ((void *)i, (void *)x) < 0)
            i += qs_width;
        while (qs_compare ((void *)j, (void *)x) > 0)
            j -= qs_width;
        if (i < j)
            {
            memswap (i, j, qs_width);
            if (x == i) x = j;
            else if (x == j) x = i;
            }
        if (i <= j)
            {
            i += qs_width;                       /* (almost) no danger */
            if (j > l) j -= qs_width;            /* avoid wrap-around */
            }
        } while (i <= j);
    if (j-l < r-i)
        {
        if (l < j) qsort1 (l, j);
        if (i < r) {l = i; goto redo;}      /* qsort1 (i, r) */
        }
    else
        {
        if (i < r) qsort1 (i, r);
        if (l < j) {r = j; goto redo;}      /* qsort1 (l, j) */
        }
    }


static void memswap (void *p1, void *p2, size_t size)
    {
    char *s1, *s2, c;

    s1 = p1; s2 = p2;
    while (size > 0)
        {
        c = *s1; *s1++ = *s2; *s2++ = c;
        --size;
        }
    }
