#
# /emx/lib/math/makefile
#
GAS=as
GCPP=cpp
GCC=gcc -O -I/emx/include -DUSE_FLOATING_POINT -Wall
AR=ar
I=/emx/include/
E=$(I)sys/emx.h

LIBC=../libc.a

.SUFFIXES: .s .o

.c.o:
	$(GCC) -c $*.c

.s.o:
	$(GCPP) -P -$$ $< | $(GAS) -o $@

default:    $(LIBC)

clean:
	-del *.o

sin.o: sin.s
cos.o: cos.s
tan.o: tan.s
sinh.o: sinh.c $(I)stdio.h $(I)math.h
cosh.o: cosh.c $(I)stdio.h $(I)math.h
tanh.o: tanh.c $(I)stdio.h $(I)math.h
atan.o: atan.s
atan2.o: atan2.s
asin.o: asin.s
acos.o: acos.s
sqrt.o: sqrt.s
exp.o: exp.s
log.o: log.s
log10.o: log10.s
fabs.o: fabs.s
ceil.o: ceil.s
floor.o: floor.s
_fixunsd.o: _fixunsd.c
_fxam.o: _fxam.s
modf.o: modf.s
ldexp.o: ldexp.s
pow.o: pow.s

$(LIBC): sin.o cos.o tan.o atan.o atan2.o asin.o acos.o \
         sinh.o cosh.o tanh.o \
         sqrt.o exp.o log.o log10.o fabs.o ceil.o floor.o \
         modf.o ldexp.o pow.o _fixunsd.o _fxam.o \
    math.mod
	upda math.mod math.res $(LIBC)
	-$(AR) dv $(LIBC) __.SYMDEF
	$(AR) rv $(LIBC) @math.res
	$(AR) sv $(LIBC)
