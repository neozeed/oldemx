/* ptrace.c (emx/gcc) -- Copyright (c) 1992 by Eberhard Mattes */

#include <sys/emx.h>
#include <sys/ptrace.h>

int ptrace (int request, int pid, int addr, int data)
    {
    return (__ptrace (request, pid, addr, data));
    }
