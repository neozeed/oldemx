#
# /emx/lib/os2/makefile
#
GAS=as
GCPP=cpp
GCC=gcc -O -I/emx/include -DUSE_FLOATING_POINT
AR=ar
I=/emx/include/
E=$(I)sys/emx.h

LIBOS2=../libos2.a

.SUFFIXES: .s .o

.c.o:
	$(GCC) -c $*.c

.s.o:
	$(GAS) -o $@ $<

default:    $(LIBOS2)

clean:
        del *.o
        del os2file1.s
        del os2file2.s
        del os2file3.s
        del os2mem1.s
        del os2mem2.s
        del os2mem3.s
        del os2nls1.s
        del os2nls2.s

os2file1.s os2file2.s os2file3.s: os2file.imp
        emximp os2file.imp

os2mem1.s os2mem2.s os2mem3.s: os2mem.imp
        emximp os2mem.imp

os2nls1.s os2nls2.s: os2nls.imp
        emximp os2nls.imp

doscalls.o: doscalls.s
os2bad.o: os2bad.c
os2file1.o: os2file1.s
os2file2.o: os2file2.s
os2file3.o: os2file3.s
os2mem1.o: os2mem1.s
os2mem2.o: os2mem2.s
os2mem3.o: os2mem3.s
os2nls1.o: os2nls1.s
os2nls2.o: os2nls2.s

$(LIBOS2): doscalls.o os2bad.o os2file1.o os2file2.o os2file3.o \
           os2mem1.o os2mem2.o os2mem3.o os2nls1.o os2nls2.o \
           os2.mod
        upda os2.mod os2.res $(LIBOS2)
        -$(AR) dv $(LIBOS2) __.SYMDEF
        $(AR) rv $(LIBOS2) @os2.res
        $(AR) sv $(LIBOS2)
