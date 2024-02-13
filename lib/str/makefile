#
# /emx/lib/str/makefile
#
GAS=as
GCPP=cpp
GCC=gcc -O -I/emx/include -DUSE_FLOATING_POINT -Wall
AR=ar
I=/emx/include/
E=$(I)sys/emx.h

LIBC=../libc.a

.SUFFIXES: .s

.c.o:
	$(GCC) -c $*.c

.s.o:
	$(GCPP) -P -$$ $< | $(GAS) -o $@

default:    $(LIBC)

clean:
	-del *.o

memccpy.o: memccpy.c $(I)string.h
memchr.o: memchr.s $(I)string.h
memcmp.o: memcmp.s $(I)string.h
memcpy.o: memcpy.s $(I)string.h
memcount.o: memcount.s $(I)string.h
memicmp.o: memicmp.c $(I)string.h $(I)ctype.h
memmove.o: memmove.s $(I)string.h
memset.o: memset.s $(I)string.h
strcat.o: strcat.s $(I)string.h
strchr.o: strchr.c $(I)string.h
strcmp.o: strcmp.c $(I)string.h
strcpy.o: strcpy.s $(I)string.h
strcspn.o: strcspn.c $(I)string.h
strdup.o: strdup.c $(I)string.h $(I)stdlib.h
strerror.o: strerror.c $(I)string.h $(I)stdlib.h
stricmp.o: stricmp.c $(I)string.h $(I)ctype.h
strlen.o: strlen.s $(I)string.h
strlwr.o: strlwr.c $(I)string.h $(I)ctype.h
strncat.o: strncat.c $(I)string.h
strncmp.o: strncmp.c $(I)string.h
strncpy.o: strncpy.c $(I)string.h
strnicmp.o: strnicmp.c $(I)string.h $(I)ctype.h
strnset.o: strnset.c $(I)string.h
strpbrk.o: strpbrk.c $(I)string.h
strrchr.o: strrchr.c $(I)string.h
strrev.o: strrev.c $(I)string.h
strset.o: strset.c $(I)string.h
strspn.o: strspn.c $(I)string.h
strstr.o: strstr.c $(I)string.h
strtok.o: strtok.c $(I)string.h
strupr.o: strupr.c $(I)string.h $(I)ctype.h

bcmp.o: bcmp.s $(I)strings.h
bcopy.o: bcopy.s $(I)strings.h
bzero.o: bzero.s $(I)strings.h
index.o: index.c $(I)strings.h
rindex.o: rindex.c $(I)strings.h

$(LIBC): memset.o memchr.o memcpy.o memccpy.o memcmp.o memmove.o memicmp.o \
    strlen.o strchr.o strrchr.o strstr.o strcpy.o strcat.o strset.o strtok.o \
    strdup.o strrev.o strspn.o strcspn.o strcmp.o stricmp.o strerror.o \
    strlwr.o strupr.o strpbrk.o strncpy.o strncat.o strnset.o strncmp.o \
    strnicmp.o memcount.o \
    bcmp.o bcopy.o bzero.o index.o rindex.o \
    str.mod
	upda str.mod str.res $(LIBC)
	-$(AR) dv $(LIBC) __.SYMDEF
	$(AR) rv $(LIBC) @str.res
	$(AR) sv $(LIBC)
