#
# /emx/lib/makefile
#
GAS=\emx\bin\as
GCPP=\emx\bin\cpp
GCC=\emx\bin\gcc -O -I/emx/include -DUSE_FLOATING_POINT
AR=\emx\bin\ar
I=/emx/include/
E=$(I)sys/emx.h

LIBC=libc.a
LIBG=libg.a
LIBOS2=libos2.a
CRT0=/emx/lib/crt0.o

.c.o:
	$(GCC) -c $*.c

default:    $(CRT0) libc libos2 $(LIBG)

clean:
        -del *.o
        -del $(LIBC)
        -del $(LIBG)
        -del $(LIBOS2)

$(CRT0): misc/crt0.s
        $(GCPP) -P misc/crt0.s | $(GAS) -o $@

libc:
        cd io
        $(MAKE)
        cd ..\str
        $(MAKE)
        cd ..\misc
        $(MAKE)
        cd ..\math
        $(MAKE)
        cd ..

libos2:
        cd os2
        $(MAKE)
        cd..

$(LIBG):
        $(AR) sv $(LIBG)
