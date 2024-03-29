# makefile -- changed for emx by Eberhard Mattes -- Jan 1992

!INCLUDE /emx/include/makefile.mak

YACC=bison -y -v
SHELL=/bin/sh
MAKE=make

HAVE_VPRINTF_DEFINE = -DHAVE_VPRINTF

GLOBAL_CFLAGS = -g -DEMX
CFLAGS = -I. $(HAVE_VPRINTF_DEFINE) $(GLOBAL_CFLAGS)
LDFLAGS = $(CFLAGS)

OBSTACK = obstack.o
OBSTACK1 = obstack.o

REGEX = regex.o
REGEX1 = regex.o

ALLOCA = 
ALLOCA1 =

GNU_MALLOC =

MALLOC_FLAGS = $(CFLAGS) -Drcheck -Dbotch=fatal_dump_core -DMSTATS

SYSV_DEFINE =

TERMCAP = -ltermcap

CLIBS = $(ADD_FILES) $(TERMCAP)

ADD_FILES = $(OBSTACK) $(REGEX) $(ALLOCA) $(GNU_MALLOC)
ADD_DEPS = $(OBSTACK1) $(REGEX1) $(ALLOCA1) $(GNU_MALLOC)

SFILES = blockframe.c breakpoint.c dbxread.c coffread.c command.c core.c \
	 environ.c eval.c expprint.c findvar.c infcmd.c inflow.c infrun.c \
	 kdb-start.c main.c printcmd.c \
	 remote.c source.c stack.c standalone.c stuff.c symmisc.c symtab.c \
	 utils.c valarith.c valops.c valprint.c values.c version.c expread.y \
	 xgdb.c

DEPFILES = umax-dep.c gould-dep.c default-dep.c sun3-dep.c \
	   sparc-dep.c hp9k320-dep.c hp300bsd-dep.c news-dep.c i386-dep.c \
	   symmetry-dep.c convex-dep.c altos-dep.c isi-dep.c

PINSNS = gld-pinsn.c i386-pinsn.c sparc-pinsn.c vax-pinsn.c m68k-pinsn.c \
         ns32k-pinsn.c convex-pinsn.c

HFILES = command.h defs.h environ.h expression.h frame.h getpagesize.h \
	 inferior.h symseg.h symtab.h value.h wait.h \
         stab_gnu.h

OPCODES = m68k-opcode.h pn-opcode.h sparc-opcode.h npl-opcode.h vax-opcode.h \
	  ns32k-opcode.h convex-opcode.h

MFILES = m-hp9k320.h m-hp300bsd.h m-i386.h m-i386gas.h \
  m-i386-sv32.h m-i386g-sv32.h m-isi.h m-merlin.h \
  m-altos.h m-news.h m-newsos3.h m-npl.h m-pn.h \
  m-sparc.h m-sun2.h m-sun3.h m-sun2os4.h \
  m-sun3os4.h m-sun4os4.h m-umax.h m-vax.h m-symmetry.h m-convex.h

READLINE = readline.c history.c funmap.c \
  emacs_keymap.c vi_keymap.c vi_mode.c keymaps.c \
  readline.h history.h keymaps.h chardefs.h \
  inc-readline.texinfo inc-history.texinfo \
  Makefile ChangeLog

REMOTE_EXAMPLES = remote-sa.m68k.shar remote-multi.shar

POSSLIBS = obstack.h obstack.c regex.c regex.h malloc.c alloca.c

TESTS = testbpt.c testfun.c testrec.c testreg.c testregs.c

OTHERS = Makefile.dist createtags config.gdb ChangeLog README TAGS \
         gdb.texinfo .gdbinit COPYING expread.c stab.def \
	 XGDB-README copying.c Projects Convex.notes copying.awk hp-include

TAGFILES = $(SFILES) $(DEPFILES) $(PINSNS) $(HFILES) $(OPCODES) $(MFILES) \
           $(POSSLIBS)
TARFILES = $(TAGFILES) $(OTHERS) $(REMOTE_EXAMPLES)

OBS = main.o blockfra.o breakpoi.o findvar.o stack.o source.o \
    values.o eval.o valops.o valarith.o valprint.o printcmd.o \
    symtab.o symmisc.o coffread.o dbxread.o infcmd.o infrun.o remote.o \
    command.o utils.o expread.o expprint.o pinsn.o environ.o version.o \
    copying.o $(READLINEOBS)

TSOBS = core.o inflow.o dep.o

NTSOBS = standalone.o

TSSTART = /lib/crt0.o

NTSSTART = kdb-start.o

RL_LIB = readline/libreadline.a

TARGET_ARCH=

gdb : $(OBS) $(TSOBS) $(ADD_DEPS) $(RL_LIB) gdb.ld
        $(CC) $(LDFLAGS) -o gdb init.c @gdb.ld $(RL_LIB) $(CLIBS)

gdb1 : gdb
        copy gdb gdb1

Makefile : Makefile.dist
        copy Makefile.dist tmp.c
	$(CC) -E >Makefile tmp.c $(MD) "-DM_MAKEDEFINE=$(MD)"
        -del tmp.c

kdb : $(NTSSTART) $(OBS) $(NTSOBS) $(ADD_DEPS) $(RL_LIB)
	$(CC) $(LDFLAGS) -c init.c $(CLIBS) 
        $(LD) -o kdb $(NTSSTART) $(OBS) $(NTSOBS) init.o $(RL_LIB) -lc $(CLIBS)

TAGS: $(TAGFILES)
        createtags $(TAGFILES)
tags: TAGS

gdb.tar: $(TARFILES)
	rm -f gdb.tar
	mkdir dist-gdb
        cd dist-gdb ; for i in $(TARFILES) ; do ln -s ../$$i . ; done
	mkdir dist-gdb/readline
        cd dist-gdb/readline ; for i in $(READLINE) ; do ln -s ../../readline/$$i . ; done
	tar chf gdb.tar dist-gdb
	rm -rf dist-gdb

gdb.tar.Z: gdb.tar
	if [ -f gdb.tar.Z ]; then rm -f gdb.tar.Z; fi
	compress gdb.tar

clean:
	-del *.o
	-del gdb

distclean: clean expread.c TAGS
	rm -f dep.c opcode.h param.h pinsn.c config.status
	rm -f y.output yacc.acts yacc.tmp
        rm -f $(TESTS) Makefile

realclean: clean
        rm -f expread.c TAGS
	rm -f dep.c opcode.h param.h pinsn.c config.status
	rm -f Makefile

xgdb.o : defs.h param.h symtab.h frame.h

copying.c : COPYING copying.awk
        gawk -f copying.awk < COPYING > copying.c

expread.c : expread.y
	@echo 'Expect 4 shift/reduce conflict.'
        $(YACC) -o expread.c expread.y

expread.o : expread.c defs.h param.h symtab.h frame.h expression.h
        $(CC) -c $(CFLAGS) expread.c

readline/libreadline.a : force_update
        cd readline ; $(MAKE) "SYSV=$(SYSV_DEFINE)" \
                "DEBUG_FLAGS=$(GLOBAL_CFLAGS)" "CC=$(CC)" libreadline.a

force_update :

malloc.o : malloc.c
        $(CC) -c $(MALLOC_FLAGS) malloc.c

dep.o : dep.c config.status defs.h param.h frame.h inferior.h obstack.h

pinsn.o : pinsn.c config.status defs.h param.h symtab.h obstack.h symseg.h \
	  frame.h opcode.h

blockframe.o : defs.h param.h config.status symtab.h obstack.h symseg.h frame.h 
breakpoint.o : defs.h param.h config.status symtab.h obstack.h symseg.h frame.h
coffread.o : defs.h param.h config.status 
command.o : command.h defs.h
core.o : defs.h  param.h config.status
dbxread.o : param.h config.status defs.h symtab.h obstack.h symseg.h \
            stab_gnu.h
environ.o : environ.h 
eval.o : defs.h  param.h config.status symtab.h obstack.h symseg.h value.h expression.h 
expprint.o : defs.h symtab.h obstack.h symseg.h param.h config.status expression.h
findvar.o : defs.h param.h config.status symtab.h obstack.h symseg.h frame.h value.h 
infcmd.o : defs.h  param.h config.status symtab.h obstack.h symseg.h frame.h inferior.h \
	   environ.h value.h
inflow.o : defs.h  param.h config.status frame.h inferior.h
infrun.o : defs.h  param.h config.status symtab.h obstack.h symseg.h frame.h inferior.h \
	   wait.h
kdb-start.o : defs.h param.h config.status 
main.o : defs.h  command.h param.h config.status
malloc.o :  getpagesize.h
obstack.o : obstack.h 
printcmd.o :  defs.h param.h config.status frame.h symtab.h obstack.h symseg.h value.h \
	      expression.h 
regex.o : regex.h 
remote.o : defs.h  param.h config.status frame.h inferior.h wait.h
source.o : defs.h  symtab.h obstack.h symseg.h param.h config.status
stack.o :  defs.h param.h config.status symtab.h obstack.h symseg.h frame.h 
standalone.o : defs.h param.h config.status symtab.h obstack.h symseg.h frame.h \
	       inferior.h wait.h 
symmisc.o : defs.h symtab.h obstack.h symseg.h obstack.h 
symtab.o : defs.h  symtab.h obstack.h symseg.h param.h config.status  obstack.h
utils.o : defs.h  param.h config.status 
valarith.o : defs.h param.h config.status symtab.h obstack.h symseg.h value.h expression.h 
valops.o :  defs.h param.h config.status symtab.h obstack.h symseg.h value.h frame.h \
	    inferior.h
valprint.o :  defs.h param.h config.status symtab.h obstack.h symseg.h value.h 
values.o :  defs.h param.h config.status symtab.h obstack.h symseg.h value.h 

robotussin.h : getpagesize.h   
symtab.h : obstack.h symseg.h 
