#
# /emx/lib/misc/makefile
#
GAS=as
GCPP=cpp
GCC=gcc -O -I/emx/include -DUSE_FLOATING_POINT
AR=ar
I=/emx/include/
E=$(I)sys/emx.h

LIBC=../libc.a

.SUFFIXES: .s

.c.o:
	$(GCC) -c $*.c

.s.o:
	$(GCPP) -P $< | $(GAS) -o $@

default:    $(LIBC)

clean:
        del *.o

abort.o: abort.c $(I)stdlib.h $(I)io.h $(I)string.h
alarm.o: alarm.c $(I)stdlib.h $(E)
atexit.o: atexit.c $(I)stdlib.h $(E)
atoi.o: atoi.c $(I)stdlib.h
atol.o: atol.c $(I)stdlib.h
atof.o: atof.c $(I)math.h $(I)stdlib.h
bsearch.o: bsearch.c $(I)stdlib.h
ctype.o: ctype.c $(I)ctype.h
exit.o: exit.c $(I)stdlib.h $(E)
getcwd.o: getcwd.c $(I)stdlib.h $(I)string.h $(I)errno.h
getenv.o: getenv.c $(I)stdlib.h $(I)string.h
getopt.o: getopt.c $(I)getopt.h $(I)stdio.h $(I)stdlib.h $(I)string.h
getpages.o: getpages.c $(I)stdlib.h
getuid.o: getuid.c
itoa.o: itoa.c $(I)stdlib.h
ltoa.o: ltoa.c $(I)stdlib.h
mkdir.o: mkdir.c $(E) $(I)stdlib.h $(I)errno.h
perror.o: perror.c $(I)stdlib.h
prtc.o: prtc.c $(E) $(I)io.h
prti.o: prti.c $(E) $(I)io.h $(I)string.h $(I)stdlib.h
prts.o: prts.c $(E) $(I)io.h $(I)string.h
putenv.o: putenv.c $(I)stdlib.h $(I)string.h $(I)errno.h $(E)
pwd.o: pwd.c $(I)stdio.h $(I)pwd.h
qsort.o: qsort.c $(I)stdlib.h
rand.o: rand.c $(I)stdlib.h
rmdir.o: rmdir.c $(E) $(I)stdlib.h $(I)errno.h
sleep.o: sleep.c $(I)stdlib.h $(E)
strtol.o: strtol.c $(I)stdlib.h $(I)limits.h $(I)errno.h
strtod.o: strtod.c $(I)math.h $(I)ctype.h $(E)
syserr.o: syserr.c
ulimit.o: ulimit.c $(I)stdlib.h $(I)errno.h
ultoa.o: ultoa.c $(I)stdlib.h
_assert.o: _assert.c $(I)stdlib.h $(I)stdio.h $(I)assert.h
_defext.o: _defext.c $(I)stdlib.h $(I)string.h
_respons.o: _respons.c $(I)stdlib.h $(I)stdio.h $(I)string.h $(E)
_searche.o: _searche.c $(I)stdlib.h $(I)string.h $(I)io.h
_wildcar.o: _wildcar.c $(I)stdlib.h $(I)stdio.h $(I)string.h $(E)
_startup.o: _startup.c $(I)stdio.h
free.o: free.c $(I)stdlib.h
malloc.o: malloc.c $(E) $(I)stdlib.h
heapchk.o: heapchk.c $(E) $(I)stdlib.h $(I)string.h
calloc.o: calloc.c $(I)stdlib.h $(I)string.h
realloc.o: realloc.c $(I)stdlib.h
_expand.o: _expand.c $(E) $(I)stdlib.h
_msize.o: _msize.c $(I)stdlib.h
setjmp.o: setjmp.s $(I)setjmp.h
execve.o: execve.c $(I)process.h
spawnv.o: spawnv.c $(I)process.h $(I)stddef.h
spawnve.o: spawnve.c $(E) $(I)stdlib.h $(I)process.h $(I)string.h \
                     $(I)errno.h
spawnvp.o: spawnvp.c $(I)process.h $(I)stddef.h
spawnvpe.o: spawnvpe.c $(E) $(I)process.h
system.o: system.c $(I)process.h $(I)stdlib.h $(I)string.h $(I)errno.h
wait.o: wait.c $(E) $(I)stdlib.h $(I)process.h $(I)errno.h
_path.o: _path.c $(I)string.h $(I)stdlib.h $(I)errno.h
asctime.o: asctime.c $(I)time.h $(I)string.h
clock.o: clock.c $(E)
ctime.o: ctime.c $(I)time.h
difftime.o: difftime.c $(I)time.h
gmtime.o: gmtime.c $(I)time.h $(I)stdlib.h
localtim.o: localtim.c $(I)time.h
mktime.o: mktime.c $(I)time.h $(E)
time.o: time.c $(E)
times.o: times.c $(E) $(I)time.h $(I)sys/times.h
utimes.o: utimes.c $(I)time.h $(I)sys/time.h $(I)sys/utime.h $(E) \
                   $(I)errno.h $(I)io.h $(I)fcntl.h
dirent.o: dirent.c $(E) $(I)stdlib.h $(I)sys/types.h $(I)sys/stat.h \
             $(I)dirent.h $(I)sys/dirent.h $(I)io.h $(I)string.h $(I)errno.h
div.o: div.s $(I)stdlib.h
syscalls.o: syscalls.s

$(LIBC): prtc.o prts.o prti.o \
    _startup.o \
    exit.o abort.o _assert.o _defext.o syserr.o itoa.o atoi.o atol.o qsort.o \
    ltoa.o ulimit.o strtol.o atexit.o ultoa.o perror.o rand.o pwd.o getuid.o \
    free.o malloc.o heapchk.o calloc.o _msize.o _expand.o realloc.o getopt.o \
    getenv.o putenv.o ctype.o bsearch.o chdir.o mkdir.o rmdir.o getcwd.o \
    getpages.o _respons.o _searche.o _wildcar.o dirent.o alarm.o sleep.o \
    setjmp.o atof.o strtod.o div.o syscalls.o \
    asctime.o localtim.o mktime.o ctime.o gmtime.o time.o clock.o utimes.o \
    times.o difftime.o \
    execve.o spawnv.o spawnve.o spawnvp.o spawnvpe.o _path.o system.o wait.o \
    misc.mod
        upda misc.mod misc.res $(LIBC)
        -$(AR) dv $(LIBC) __.SYMDEF
        $(AR) rv $(LIBC) @misc.res
        $(AR) sv $(LIBC)
