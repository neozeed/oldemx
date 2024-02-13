#
# /emx/lib/misc/makefile
#
GAS=as
GCPP=cpp
GCC=gcc -O -I/emx/include -DUSE_FLOATING_POINT -Wall
AR=ar
I=/emx/include/
E=$(I)sys/emx.h
SIGNAL=$(I)signal.h $(I)sys/signal.h
FCNTL=$(I)fcntl.h $(I)sys/fcntl.h

LIBC=../libc.a
LIBGCC=../libgcc.a

.SUFFIXES: .s

.c.o:
	$(GCC) -c $*.c

.s.o:
	$(GCPP) -P -$$ $< | $(GAS) -o $@

default:    $(LIBC) $(LIBGCC)

clean:
	-del *.o

abort.o: abort.c $(I)stdlib.h $(SIGNAL) $(E)
alarm.o: alarm.c $(I)stdlib.h $(E)
atexit.o: atexit.c $(I)stdlib.h $(E)
atoi.o: atoi.c $(I)stdlib.h
atol.o: atol.c $(I)stdlib.h
atof.o: atof.c $(I)math.h $(I)stdlib.h
bsearch.o: bsearch.c $(I)stdlib.h
chdir.o: chdir.c $(I)stdlib.h $(I)errno.h $(E)
ctype.o: ctype.c $(I)ctype.h
exit.o: exit.c $(I)stdlib.h $(E)
getcwd.o: getcwd.c $(I)stdlib.h $(I)string.h $(I)errno.h $(I)sys/param.h $(E)
getenv.o: getenv.c $(I)stdlib.h $(I)string.h
getopt.o: getopt.c $(I)getopt.h $(I)stdio.h $(I)stdlib.h $(I)string.h
getpages.o: getpages.c $(I)stdlib.h
getpid.o: getpid.c $(E) $(I)process.h
getuid.o: getuid.c
itoa.o: itoa.c $(I)stdlib.h
kill.o: kill.c $(E) $(SIGNAL)
ltoa.o: ltoa.c $(I)stdlib.h
mkdir.o: mkdir.c $(E) $(I)stdlib.h $(I)errno.h
perror.o: perror.c $(I)stdlib.h
ptrace.o: ptrace.c $(I)sys/ptrace.h
putenv.o: putenv.c $(I)stdlib.h $(I)string.h $(I)errno.h $(E)
pwd.o: pwd.c $(I)stdio.h $(I)pwd.h
qsort.o: qsort.c $(I)stdlib.h
raise.o: raise.c $(E) $(SIGNAL)
rand.o: rand.c $(I)stdlib.h
rmdir.o: rmdir.c $(E) $(I)stdlib.h $(I)errno.h
sbrk.o: sbrk.c $(E) $(I)stdlib.h
signal.o: signal.c $(E) $(SIGNAL)
sleep.o: sleep.c $(I)stdlib.h $(E)
strtol.o: strtol.c $(I)stdlib.h $(I)limits.h $(I)errno.h
strtod.o: strtod.c $(I)math.h $(I)ctype.h $(E)
syserr.o: syserr.c
ulimit.o: ulimit.c $(I)stdlib.h $(I)errno.h $(E)
ultoa.o: ultoa.c $(I)stdlib.h
umask.o: umask.c $(E) $(I)stdlib.h
_abspath.o: _abspath.c $(I)stdlib.h $(I)errno.h $(I)string.h $(I)alloca.h \
            $(I)sys/param.h $(E)
_assert.o: _assert.c $(I)stdlib.h $(I)stdio.h $(I)assert.h
_chdir2.o: _chdir2.c $(I)stdlib.h $(I)errno.h $(E)
_chdrive.o: _chdrive.c $(I)stdlib.h $(E)
_cleanup.o: _cleanup.c $(I)stdio.h
_core.o: _core.c $(I)stdlib.h $(E)
_defext.o: _defext.c $(I)stdlib.h $(I)string.h
_expand.o: _expand.c $(E) $(I)stdlib.h
_fngetdr.o: _fngetdr.c $(I)stdlib.h
_fullpat.o: _fullpat.c $(I)stdlib.h $(I)stdio.h $(I)string.h $(I)alloca.h \
                       $(I)sys/param.h $(I)errno.h $(E)
_getcwd1.o: _getcwd1.c $(I)stdlib.h $(E)
_getcwd2.o: _getcwd2.c $(I)stdlib.h $(I)string.h $(I)errno.h $(I)sys/param.h $(E)
_getdriv.o: _getdriv.c $(I)stdlib.h $(E)
_msize.o: _msize.c $(I)stdlib.h
_readkbd.o: _readkbd.c $(I)stdlib.h $(E)
_respons.o: _respons.c $(I)stdlib.h $(I)stdio.h $(I)string.h $(E)
_scrsize.o: _scrsize.c $(E)
_searche.o: _searche.c $(I)stdlib.h $(I)string.h $(I)io.h
_startup.o: _startup.c $(I)stdlib.h $(I)stdio.h $(E) $(FCNTL) $(I)sys/ioctl.h
_swchar.o: _swchar.c $(I)stdlib.h $(E)
_syserrn.o: _syserrn.c $(E)
_wildcar.o: _wildcar.c $(I)stdlib.h $(I)stdio.h $(I)string.h $(E)
free.o: free.c $(I)stdlib.h
malloc.o: malloc.c $(E) $(I)stdlib.h
heapchk.o: heapchk.c $(E) $(I)stdlib.h $(I)string.h
calloc.o: calloc.c $(I)stdlib.h $(I)string.h
realloc.o: realloc.c $(I)stdlib.h
setjmp.o: setjmp.s $(I)setjmp.h
execve.o: execve.c $(I)process.h
spawnl.o: spawnl.c $(I)process.h $(I)stddef.h $(I)stdarg.h
spawnle.o: spawnle.c $(I)process.h $(I)stddef.h $(I)stdarg.h
spawnlp.o: spawnlp.c $(I)process.h $(I)stddef.h $(I)stdarg.h
spawnlpe.o: spawnlpe.c $(I)process.h $(I)stddef.h $(I)stdarg.h
spawnv.o: spawnv.c $(I)process.h $(I)stddef.h
spawnve.o: spawnve.c $(E) $(I)stdlib.h $(I)process.h $(I)string.h \
                     $(I)errno.h
spawnvp.o: spawnvp.c $(I)process.h $(I)stddef.h
spawnvpe.o: spawnvpe.c $(E) $(I)process.h $(I)stdlib.h
system.o: system.c $(I)process.h $(I)stdlib.h $(I)string.h $(I)errno.h \
                   $(I)io.h
wait.o: wait.c $(E) $(I)stdlib.h $(I)process.h $(I)errno.h
_path.o: _path.c $(I)string.h $(I)stdlib.h $(I)errno.h $(I)io.h
asctime.o: asctime.c $(I)time.h $(I)string.h
clock.o: clock.c $(E)
ctime.o: ctime.c $(I)time.h
difftime.o: difftime.c $(I)time.h
ftime.o: ftime.c $(E) $(I)sys/timeb.h $(I)time.h
gettimeo.o: gettimeo.c $(E) $(I)sys/time.h $(I)time.h
gmtime.o: gmtime.c $(I)time.h $(I)stdlib.h
localtim.o: localtim.c $(I)time.h
mktime.o: mktime.c $(I)time.h $(E)
time.o: time.c $(I)sys/timeb.h $(I)time.h
times.o: times.c $(E) $(I)time.h $(I)sys/times.h
utimes.o: utimes.c $(I)time.h $(I)sys/time.h $(I)sys/utime.h $(E) \
                   $(I)errno.h $(I)io.h $(I)fcntl.h
dirent.o: dirent.c $(E) $(I)stdlib.h $(I)sys/types.h $(I)sys/stat.h \
             $(I)dirent.h $(I)sys/dirent.h $(I)io.h $(I)string.h $(I)errno.h
div.o: div.s $(I)stdlib.h
syscalls.o: syscalls.s
_main.o: _main.c
_probe.o: _probe.s
_udivsi3.o: _udivsi3.s
_divsi3.o: _divsi3.s
_fixdfsi.o: _fixdfsi.s

$(LIBC): _startup.o _cleanup.o syscalls.o \
    exit.o abort.o _assert.o syserr.o itoa.o atoi.o atol.o qsort.o \
    ltoa.o ulimit.o strtol.o atexit.o ultoa.o perror.o rand.o pwd.o getuid.o \
    free.o malloc.o heapchk.o calloc.o _msize.o _expand.o realloc.o getopt.o \
    getenv.o putenv.o ctype.o bsearch.o chdir.o mkdir.o rmdir.o getcwd.o \
    getpages.o _respons.o _searche.o _wildcar.o dirent.o alarm.o sleep.o \
    setjmp.o atof.o strtod.o div.o sbrk.o umask.o getpid.o signal.o raise.o \
    asctime.o localtim.o mktime.o ctime.o gmtime.o time.o clock.o utimes.o \
    times.o difftime.o ftime.o gettimeo.o kill.o ptrace.o \
    execve.o spawnv.o spawnve.o spawnvp.o spawnvpe.o _path.o system.o wait.o \
    spawnl.o spawnle.o spawnlp.o spawnlpe.o \
    _defext.o _fngetdr.o _fullpat.o _getcwd1.o _getcwd2.o _chdir2.o \
    _swchar.o _readkbd.o _getdriv.o _core.o _chdrive.o _scrsize.o _abspath.o \
    _syserrn.o \
    misc.mod
	upda misc.mod misc.res $(LIBC)
	-$(AR) dv $(LIBC) __.SYMDEF
	$(AR) rv $(LIBC) @misc.res
	$(AR) sv $(LIBC)

$(LIBGCC): _main.o _probe.o _udivsi3.o _divsi3.o _fixdfsi.o \
    libgcc.mod
	upda libgcc.mod libgcc.res $(LIBGCC)
	-$(AR) dv $(LIBGCC) __.SYMDEF
	$(AR) rv $(LIBGCC) @libgcc.res
	$(AR) sv $(LIBGCC)
