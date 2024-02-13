#
# /emx/lib/makefile
#
GAS=\emx\bin\as
GCPP=\emx\bin\cpp
GCC=\emx\bin\gcc -O -I/emx/include -DUSE_FLOATING_POINT -Wall
AR=\emx\bin\ar
I=/emx/include/
E=$(I)sys/emx.h

LIBC=libc.a
LIBG=libg.a
LIBGCC=libgcc.a
LIBOS2=libos2.a
CRT0=/emx/lib/crt0.o
BINMODE=/emx/lib/binmode.o

.c.o:
	$(GCC) -c $*.c

default:    $(CRT0) $(BINMODE) libc libgcc libos2 $(LIBG)

clean:
	-del *.o
	-del $(LIBC)
	-del $(LIBG)
	-del $(LIBGCC)
	-del $(LIBOS2)

cleanall: clean
	cd io
	$(MAKE) clean
	cd ..\str
	$(MAKE) clean
	cd ..\misc
	$(MAKE) clean
	cd ..\math
	$(MAKE) clean
	cd ..\os2
	$(MAKE) clean
	cd ..

$(CRT0): misc/crt0.s
	$(GCPP) -P -$$ misc/crt0.s | $(GAS) -o $@

$(BINMODE): io/binmode.c
	$(GCC) -c -o $(BINMODE) io/binmode.c

libc libgcc:
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
