/* sbrk.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <stdlib.h>

void *sbrk (int incr)
   {
   return (__sbrk (incr));
   }
