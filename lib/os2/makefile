#
# /emx/lib/os2/makefile
#
GAS=as
GCC=gcc -O -I/emx/include -DUSE_FLOATING_POINT -Wall
AR=ar
I=/emx/include/
E=$(I)sys/emx.h
EMXIMP=emximp -pdoscalls -ppmwin -ppmgpi

LIBOS2=../libos2.a

.SUFFIXES: .s .o

.c.o:
	$(GCC) -c $*.c

.s.o:
	$(GAS) -o $@ $<

default:    $(LIBOS2)

clean:
	-del *.o
	-del os2dll1.s
	-del os2err1.s
	-del os2file1.s
	-del os2file2.s
	-del os2file3.s
	-del os2file4.s
	-del os2file5.s
	-del os2gpi1.s
	-del os2gpi2.s
	-del os2info1.s
	-del os2mem1.s
	-del os2mem2.s
	-del os2mem3.s
	-del os2nls1.s
	-del os2nls2.s
	-del os2pipe1.s
	-del os2pipe2.s
	-del os2sem1.s
	-del os2sem2.s
	-del os2sem3.s
	-del os2task1.s
	-del os2task2.s
	-del os2win1.s
	-del os2win2.s
	-del os2win3.s
	-del os2win4.s
	-del os2xcpt1.s

os2dll1.s: os2dll.imp
	$(EMXIMP) os2dll.imp

os2err1.s: os2err.imp
	$(EMXIMP) os2err.imp

os2file1.s os2file2.s os2file3.s os2file4.s os2file5.s: os2file.imp
	$(EMXIMP) os2file.imp

os2gpi1.s os2gpi2.s: os2gpi.imp
	$(EMXIMP) os2gpi.imp

os2info1.s: os2info.imp
	$(EMXIMP) os2info.imp

os2mem1.s os2mem2.s os2mem3.s: os2mem.imp
	$(EMXIMP) os2mem.imp

os2nls1.s os2nls2.s: os2nls.imp
	$(EMXIMP) os2nls.imp

os2pipe1.s os2pipe2.s: os2pipe.imp
	$(EMXIMP) os2pipe.imp

os2sem1.s os2sem2.s os2sem3.s: os2sem.imp
	$(EMXIMP) os2sem.imp

os2task1.s os2task2.s: os2task.imp
	$(EMXIMP) os2task.imp

os2win1.s os2win2.s os2win3.s os2win4.s: os2win.imp
	$(EMXIMP) os2win.imp

os2xcpt1.s: os2xcpt.imp
	$(EMXIMP) os2xcpt.imp

doscalls.o: doscalls.s
os2bad.o: os2bad.c
os2dll1.o: os2dll1.s
os2err1.o: os2err1.s
os2file1.o: os2file1.s
os2file2.o: os2file2.s
os2file3.o: os2file3.s
os2file4.o: os2file4.s
os2file5.o: os2file5.s
os2gpi1.o: os2gpi1.s
os2gpi2.o: os2gpi2.s
os2info1.o: os2info1.s
os2mem1.o: os2mem1.s
os2mem2.o: os2mem2.s
os2mem3.o: os2mem3.s
os2nls1.o: os2nls1.s
os2nls2.o: os2nls2.s
os2pipe1.o: os2pipe1.s
os2pipe2.o: os2pipe2.s
os2sem1.o: os2sem1.s
os2sem2.o: os2sem2.s
os2sem3.o: os2sem3.s
os2task1.o: os2task1.s
os2task2.o: os2task2.s
os2win1.o: os2win1.s
os2win2.o: os2win2.s
os2win3.o: os2win3.s
os2win4.o: os2win4.s
os2xcpt1.o: os2xcpt1.s
pmgpi.o: pmgpi.s
pmwin.o: pmwin.s

$(LIBOS2): doscalls.o pmgpi.o pmwin.o os2bad.o os2dll1.o os2err1.o \
           os2file1.o os2file2.o os2file3.o os2file4.o os2file5.o \
           os2gpi1.o os2gpi2.o os2info1.o \
           os2mem1.o os2mem2.o os2mem3.o os2nls1.o os2nls2.o \
           os2pipe1.o os2pipe2.o os2sem1.o os2sem2.o os2sem3.o \
           os2task1.o os2task2.o \
           os2win1.o os2win2.o os2win3.o os2win4.o os2xcpt1.o \
           os2.mod
	upda os2.mod os2.res $(LIBOS2)
	-$(AR) dv $(LIBOS2) __.SYMDEF
	$(AR) rv $(LIBOS2) @os2.res
	$(AR) sv $(LIBOS2)
