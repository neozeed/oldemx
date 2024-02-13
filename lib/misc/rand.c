/* rand.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdlib.h>

static unsigned int _rand = 1;

int rand (void)
    {
    _rand = _rand * 69069 + 5;
    return ((_rand >> 16) & 0x7fff);
    }

void srand (unsigned int seed)
    {
    _rand = seed;
    }
