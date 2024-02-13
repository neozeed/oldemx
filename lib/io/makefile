#
# /emx/lib/io/makefile
#
GAS=as
GCPP=cpp
GCC=gcc -O -I/emx/include -DUSE_FLOATING_POINT -Wall
AR=ar
I=/emx/include/
E=$(I)sys/emx.h
FCNTL=$(I)fcntl.h $(I)sys/fcntl.h

LIBC=../libc.a

.SUFFIXES: .s

.c.o:
	$(GCC) -c $*.c

.s.o:
	$(GCPP) -P -$$ $< | $(GAS) -o $@

default:    $(LIBC)

clean:
	-del *.o

access.o: access.c $(E) $(I)io.h $(I)errno.h
chmod.o: chmod.c $(I)io.h $(I)sys/types.h $(I)sys/stat.h $(E) $(I)errno.h
close.o: close.c $(E) $(I)io.h $(I)errno.h
creat.o: creat.c $(I)io.h $(FCNTL)
dup.o: dup.c $(I)io.h $(E) $(I)errno.h
dup2.o: dup2.c $(I)io.h $(E) $(I)errno.h
eof.o: eof.c $(I)io.h $(E) $(I)errno.h
fcntl.o: fcntl.c $(E) $(FCNTL) $(I)errno.h
fileleng.o: fileleng.c $(I)io.h $(E)
fstat.o: fstat.c $(I)io.h $(E) $(I)sys/types.h $(I)sys/stat.h \
                 $(I)time.h $(FCNTL) $(E)
fsync.o: fsync.c $(I)io.h $(E)
ftruncat.o: ftruncat.c $(I)io.h $(E) $(I)errno.h
ioctl.o: ioctl.c $(E) $(I)io.h $(I)stdlib.h $(I)sys/termio.h $(I)sys/ioctl.h \
                 $(I)errno.h $(I)stdarg.h
isatty.o: isatty.c $(E) $(I)io.h $(I)errno.h
lseek.o: lseek.c $(E) $(I)io.h $(I)errno.h
mktemp.o: mktemp.c $(I)io.h $(I)string.h $(I)process.h $(I)errno.h
open.o: open.c $(E) $(I)io.h $(I)stdarg.h $(I)errno.h $(FCNTL) \
               $(I)sys/types.h $(I)sys/stat.h
read.o: read.c $(E) $(I)io.h $(I)errno.h $(I)string.h $(FCNTL)
remove.o: remove.c $(E) $(I)io.h $(I)errno.h
stat.o: stat.c $(I)io.h $(FCNTL) $(I)errno.h $(I)sys/types.h $(I)sys/stat.h
tell.o: tell.c $(I)io.h $(E) $(I)errno.h
truncate.o: truncate.c $(I)io.h $(FCNTL)
unlink.o: unlink.c $(I)io.h
write.o: write.c $(E) $(I)io.h $(I)errno.h $(I)string.h $(FCNTL)
_iodata.o: _iodata.c $(E) $(FCNTL)

clearerr.o: clearerr.c $(I)stdio.h
fclose.o: fclose.c $(I)stdio.h $(I)stdlib.h $(I)io.h $(E)
fcloseal.o: fcloseal.c $(I)stdio.h $(E)
fdopen.o: fdopen.c $(I)stdio.h $(E) $(FCNTL) $(I)errno.h $(I)io.h
fflush.o: fflush.c $(I)stdio.h $(E) $(FCNTL) $(I)io.h
fgetc.o: fgetc.c $(I)stdio.h
fgetchar.o: fgetchar.c $(I)stdio.h
fgetpos.o: fgetpos.c $(I)stdio.h
fgets.o: fgets.c $(I)stdio.h
flushall.o: flushall.c $(I)stdio.h $(E)
fopen.o: fopen.c $(I)stdio.h $(E)
fprintf.o: fprintf.c $(I)stdio.h $(I)stdarg.h $(E)
fputc.o: fputc.c $(I)stdio.h
fputchar.o: fputchar.c $(I)stdio.h
fputs.o: fputs.c $(I)stdio.h $(I)string.h $(E)
fread.o: fread.c $(I)stdio.h $(I)io.h $(I)errno.h $(I)string.h $(E) $(I)stdlib.h
freopen.o: freopen.c $(I)stdio.h $(E)
fscanf.o: fscanf.c $(I)stdio.h $(I)stdarg.h $(E)
fseek.o: fseek.c $(I)stdio.h $(I)io.h $(I)errno.h $(E)
fsetpos.o: fsetpos.c $(I)stdio.h
ftell.o: ftell.c $(I)stdio.h $(I)io.h $(E)
fwrite.o: fwrite.c $(I)stdio.h $(I)io.h $(I)errno.h $(I)string.h $(E)
gets.o: gets.c $(I)stdio.h
pclose.o: pclose.c $(I)io.h $(I)process.h $(I)errno.h $(E)
pipe.o: pipe.c $(I)io.h $(I)errno.h $(FCNTL) $(E)
popen.o: popen.c $(E) $(I)stdio.h $(I)stdlib.h $(I)string.h $(I)process.h \
                 $(I)io.h $(I)unistd.h $(FCNTL) $(I)errno.h
printf.o: printf.c $(I)stdio.h $(I)stdarg.h $(E)
puts.o: puts.c $(I)stdio.h $(I)string.h $(E)
rename.o: rename.c $(I)stdio.h $(E) $(I)errno.h
rewind.o: rewind.c $(I)stdio.h
rmtmp.o: rmtmp.c $(I)stdio.h $(E)
scanf.o: scanf.c $(I)stdio.h $(I)stdarg.h $(E)
setbuf.o: setbuf.c $(I)stdio.h $(I)stdlib.h $(E)
setbuffe.o: setbuffe.c $(I)stdio.h
setmode.o: setmode.c $(I)io.h $(FCNTL) $(I)errno.h $(E)
setvbuf.o: setvbuf.c $(I)stdio.h $(E) $(I)stdlib.h
sprintf.o: sprintf.c $(I)stdio.h $(I)stdarg.h $(E) $(I)limits.h
sscanf.o: sscanf.c $(I)stdio.h $(I)stdarg.h $(E) $(I)limits.h
select.o: select.c $(I)io.h $(I)sys/types.h $(I)sys/time.h $(E) $(I)stdlib.h \
                   $(I)memory.h
stdio.o: stdio.c $(I)stdio.h $(E) $(FCNTL)
tmpfile.o: tmpfile.c $(I)stdio.h $(E) $(I)stdlib.h $(I)errno.h $(I)io.h \
                     $(I)string.h $(I)sys/param.h
ungetc.o: ungetc.c $(I)stdio.h $(E) $(I)errno.h
vfprintf.o: vfprintf.c $(I)stdio.h $(E)
vprintf.o: vprintf.c $(I)stdio.h $(E)
vsprintf.o: vsprintf.c $(I)stdio.h $(E) $(I)limits.h
_crlf.o: _crlf.c $(I)io.h $(I)string.h
_fbuf.o: _fbuf.c $(I)stdio.h $(E) $(I)stdlib.h
_fill.o: _fill.c $(I)stdio.h $(E) $(I)io.h $(I)errno.h $(FCNTL)
_flush.o: _flush.c $(I)stdio.h $(E) $(I)io.h $(I)errno.h $(FCNTL)
_fopen.o: _fopen.c $(I)stdio.h $(E) $(I)io.h $(FCNTL) $(I)errno.h
_fseekhd.o: _fseekhd.c $(I)stdio.h $(I)memory.h
_fsetmod.o: _fsetmod.c $(I)stdio.h $(I)io.h $(I)errno.h $(FCNTL)
_isterm.o: _isterm.c $(I)io.h $(E)
_newstre.o: _newstre.c $(I)stdio.h
_input.o: _input.c $(E) $(I)stdio.h $(I)stdarg.h $(I)string.h \
                   $(I)stdlib.h $(I)limits.h $(I)ctype.h
_output.o: _output.c $(E) $(I)stdio.h $(I)stdarg.h $(I)string.h \
                     $(I)stdlib.h $(I)limits.h
_seekhdr.o: _seekhdr.c $(I)io.h $(I)memory.h
_tmpbuf.o: _tmpbuf.c $(E) $(I)stdio.h $(I)io.h

$(LIBC):  read.o write.o open.o close.o _iodata.o lseek.o isatty.o access.o \
    eof.o remove.o tell.o unlink.o fileleng.o creat.o fstat.o fsync.o dup.o \
    fcntl.o pipe.o pclose.o popen.o dup2.o select.o \
    chmod.o stat.o mktemp.o ftruncat.o truncate.o fopen.o freopen.o \
    fclose.o fread.o fwrite.o fflush.o fgetc.o fputc.o fgetchar.o \
    fputchar.o fputs.o puts.o _flush.o _fill.o _fbuf.o _fopen.o stdio.o \
    flushall.o fcloseal.o clearerr.o rewind.o setvbuf.o fdopen.o ioctl.o \
    fgetpos.o fsetpos.o ftell.o fseek.o setbuf.o printf.o fprintf.o \
    sprintf.o vprintf.o vfprintf.o vsprintf.o rename.o scanf.o sscanf.o \
    fscanf.o fgets.o gets.o ungetc.o setbuffe.o setmode.o tmpfile.o rmtmp.o \
    _input.o _output.o _newstre.o _tmpbuf.o _fseekhd.o _seekhdr.o _isterm.o \
    _crlf.o _fsetmod.o \
    io.mod
	upda io.mod io.res $(LIBC)
	-$(AR) dv $(LIBC) __.SYMDEF
	$(AR) rv $(LIBC) @io.res
	$(AR) sv $(LIBC)
