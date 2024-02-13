# /emx/termcap/makefile

!INCLUDE /emx/include/makefile.mak
TERMCAP=\emx\lib\libtermc.a
CFLAGS=-DEMX

$(TERMCAP): termcap.o tparam.o
        -del $(TERMCAP)
        $(AR) rs $(TERMCAP) termcap.o tparam.o

termcap.o: termcap.c
tparam.o: tparam.c
