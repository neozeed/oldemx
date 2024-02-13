#
# /emx/test/makefile
#
# Note: this makefile is out-dated
#
CC=\emx\bin\gcc -g
L=/emx/lib/crt0.o /emx/lib/libc.a
I=/emx/include/
LINK=$(CC) -o $* $*.o

.SUFFIXES: .o .s

.c.o:
        $(CC) -c $*.c

.c.s:
        $(CC) -S $*.c

default:        sieve iotest memory timetest sort version math exec \
                sbrktest args memtest stream stdio format ctypetst debug \
                showmem.exe

clean:
        -del *.o
        -del *.exe
        -del align.s
        -del args
        -del bug
        -del ctypetst
        -del debug
        -del exec
        -del format
        -del gtest1
        -del gtest2
        -del gtest3
        -del hexdump
        -del iotest
        -del math
        -del memory
        -del memtest
        -del printf
        -del retcode
        -del sbrktest
        -del sieve
        -del sig1
        -del sig2
        -del sort
        -del stack
        -del stdio
        -del stream
        -del timetest
        -del version
        -del showmem.exe

gtest1.o:       gtest1.c $(I)io.h
gtest2.o:       gtest2.c $(I)io.h
gtest3.o:       gtest3.c $(I)stdlib.h

gtest1:         gtest1.o $(L)
        $(LINK)
gtest2:         gtest2.o $(L)
        $(LINK)
gtest3:         gtest3.o $(L)
        $(LINK)
sieve:          sieve.o $(L)
        $(LINK)
iotest:         iotest.o $(L)
        $(LINK)
sbrktest:       sbrktest.o $(L)
        $(LINK)
args:           args.o $(L)
        $(LINK)
memtest:        memtest.o $(L)
        $(LINK)
exec:           exec.o $(L)
        $(LINK)
debug:          debug.o $(L)
        $(LINK)
stream:         stream.o $(L)
        $(LINK)
stdio:          stdio.o $(L)
        $(LINK)
ctypetst:     ctypetst.o $(L)
        $(LINK)
format:         format.o $(L)
        $(LINK)
memory:         memory.o $(L)
        $(LINK)
timetest:       timetest.o $(L)
        $(LINK)
sort:           sort.o $(L)
        $(LINK)
math:           math.o $(L)
        $(LINK)
version:        version.o $(L)
        $(LINK)

sieve.o:        sieve.c $(I)stdlib.h
iotest.o:       iotest.c $(I)stdlib.h $(I)io.h $(I)fcntl.h $(I)string.h \
                $(I)errno.h
sbrktest.o:     sbrktest.c $(I)stdlib.h $(I)string.h $(I)io.h
args.o:         args.c $(I)stdio.h
memtest.o:      memtest.c $(I)sys/emx.h $(I)stdlib.h $(I)string.h $(I)io.h
exec.o:         exec.c $(I)stdio.h $(I)string.h $(I)process.h
debug.o:        debug.c $(I)stdio.h $(I)string.h $(I)process.h \
                $(I)sys/ptrace.h $(I)sys/reg.h $(I)sys/user.h
stream.o:       stream.c $(I)stdio.h $(I)stdlib.h $(I)sys/emx.h $(I)fcntl.h \
                $(I)errno.h $(I)string.h
stdio.o:        stdio.c $(I)stdio.h $(I)stdlib.h
ctypetst.o: ctypetst.c $(I)stdio.h $(I)string.h $(I)ctype.h
format.o:       format.c $(I)stdio.h
memory.o:       memory.c $(I)stdio.h $(I)string.h
timetest.o:     timetest.c $(I)stdio.h $(I)time.h
sort.o:         sort.c $(I)stdio.h $(I)stdlib.h $(I)string.h
math.o:         math.c $(I)stdio.h $(I)stdlib.h $(I)math.h
version.o:      version.c $(I)stdio.h $(I)stdlib.h

showmem.exe:    showmem.c
        $(CC) -o showmem.exe showmem.c -los2
