# Makefile for use with emx -- derived from makefile.dos by Eberhard Mattes -- Mar 1992 */
BISON=bison
BISONFLAGS=-v
LIBDEPS=$(OBSTACK)
CPPFLAGS=
CPLUS_INPUT=
GCC=d:\emx\bin\gcc
CFLAGS=
XCFLAGS=
LD=d:\emx\bin\ld
CRT0=d:\emx\lib\crt0.o

CONFIG_H=
RTL = rtl.o
RTLANAL=rtlanal.o
OBSTACK=obstack.o

# Special flags for compiling enquire.
ENQUIRE_CFLAGS = -DNO_SC -DNO_MEM -DNO_STDDEF $(GCC_CFLAGS)
ENQUIRE_LDFLAGS = $(LDFLAGS)

ALL_CFLAGS = $(CFLAGS) $(XCFLAGS)
CC=$(GCC) $(ALL_CFLAGS)
INCLUDES=-Iconfig -I.
LDFLAGS=

.SUFFIXES: .c .o

# Always use -I$(srcdir)/config when compiling.
.c.o:
	$(CC) -c $(INCLUDES) $<

# Language-specific object files for C.
C_OBJS = c-parse.o c-decl.o c-typeck.o c-lang.o c-convert.o c-lex.o \
   c-aux-info.o c-common.o

# Language-specific object files for Objectionable C.
OBJC_OBJS = objc-parse.o objc-actions.o \
   c-lex.o c-decl.o c-typeck.o c-convert.o c-aux-info.o c-common.o

# Language-specific object files for C++.
CPLUS_OBJS = cp-parse.o cp-decl.o cp-decl2.o \
   cp-typeck.o cp-type2.o cp-tree.o cp-ptree.o \
   cp-cvt.o cp-search.o cp-lex.o cp-gc.o cp-call.o \
   cp-class.o cp-init.o cp-method.o cp-except.o \
   cp-expr.o cp-pt.o cp-edsel.o cp-xref.o c-common.o \
   cp-spew.o $(CPLUS_INPUT)

# Language-independent object files.
OBJS = toplev.o version.o tree.o print-tree.o stor-layout.o fold-const.o \
 function.o stmt.o expr.o calls.o expmed.o explow.o optabs.o varasm.o \
 rtl.o print-rtl.o rtlanal.o sdbout.o dwarfout.o emit-rtl.o insn-emit.o \
 integrate.o jump.o cse.o loop.o unroll.o flow.o stupid.o combine.o \
 regclass.o local-alloc.o global-alloc.o reload.o reload1.o caller-save.o \
 insn-peep.o reorg.o sched.o final.o recog.o reg-stack.o dbxout.o \
 insn-recog.o insn-extract.o insn-output.o \
 insn-attrtab.o aux-output.o getpwd.o $(OBSTACK)

# GEN files are listed separately, so they can be built before doing parallel
#  makes for cc1 or cc1plus.  Otherwise sequent parallel make attempts to load
#  them before rtl.o is compiled.
GEN= genemit.exe genoutpu.exe genrecog.exe genextra.exe genflags.exe \
     gencodes.exe genconfi.exe genpeep.exe

RTL_H = rtl.h rtl.def machmode.h machmode.def
TREE_H = tree.h real.h tree.def machmode.h machmode.def
CPLUS_TREE_H = $(TREE_H) cp-tree.h cp-tree.def

LANGUAGES = c c++ objective-c

all : gcc cpp $(LANGUAGES)


# Define the names for selecting languages in LANGUAGES.
c : cc1
c++: cc1plus
objc: cc1obj
class-c: cc1obj
objective-c: cc1obj

compilations: $(OBJS)

gcc: gcc.o version.o $(LIBDEPS)
	$(CC) $(LDFLAGS) -o gcc gcc.o version.o $(OBSTACK)
# Go via `gccnew' to avoid `file busy' if gcc is `gcc'.
#	mv -f gccnew gcc
# Dump a specs file to make -B./ read these specs over installed ones
#	gcc -dumpspecs > specs

cc1 : $(C_OBJS) $(OBJS) $(LIBDEPS)
	$(CC) $(LDFLAGS) -o cc1 $(C_OBJS) $(OBJS) $(LIBS)

cc1plus : $(CPLUS_OBJS) $(OBJS) $(LIBDEPS)
	$(CC) $(LDFLAGS) -o cc1plus $(CPLUS_OBJS) $(OBJS) $(LIBS)

cc1obj : $(OBJC_OBJS) $(OBJS) $(LIBDEPS)
	$(CC) $(LDFLAGS) -o cc1obj $(OBJC_OBJS) $(OBJS) $(LIBS)

float.h : enquire
	-./enquire -f > float.h

# Used to compile enquire with standard cc, but have forgotten why.
# Let's try with GCC.
enquire: enquire.o gnulib
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(ENQUIRE_LDFLAGS) enquire.o -o $@
enquire.o: enquire.c cc1 cpp
	-cp enquire.c . > /dev/null 2>&1
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(CPPFLAGS) $(ENQUIRE_CFLAGS) -I. \
	    -c enquire.c

# Compiling object files from source files.

# Note that dependencies on obstack.h are not written
# because that file is not part of GCC.
# Dependencies on gvarargs.h are not written
# because all that file does, when not compiling with GCC,
# is include the system varargs.h.

# C language specific files.

c-parse.o : c-parse.c $(TREE_H) c-parse.h c-tree.h input.h flags.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -c c-parse.c
c-parse.c : c-parse.y
	$(BISON) $(BISONFLAGS) c-parse.y -o $@

c-decl.o : c-decl.c $(CONFIG_H) $(TREE_H) c-tree.h c-parse.h flags.h
c-typeck.o : c-typeck.c $(CONFIG_H) $(TREE_H) c-tree.h flags.h
c-lang.o : c-lang.c $(CONFIG_H) $(TREE_H)
c-lex.o : c-lex.c $(CONFIG_H) $(TREE_H) c-lex.h c-tree.h c-parse.h \
    input.h flags.h
c-aux-info.o : c-aux-info.c  $(CONFIG_H) $(TREE_H) c-tree.h flags.h
c-convert.o : c-convert.c $(CONFIG_H) $(TREE_H)

# C++ language specific files.

cp-parse.o : cp-parse.c $(CPLUS_TREE_H) flags.h
	$(CC) -c $(CPPFLAGS) $(INCLUDES) \
  -DPARSE_OUTPUT=\"$(PWD)/cp-parse.output\" \
  cp-parse.c

cp-parse.c cp-parse.h : cp-parse.y
	@echo expect 29 shift/reduce conflicts and 14 reduce/reduce conflicts
	$(BISON) $(BISONFLAGS) -d -o cp-parse.c cp-parse.y

cp-spew.o : cp-spew.c $(CONFIG_H) $(CPLUS_TREE_H) \
   cp-parse.h flags.h
cp-lex.o : cp-lex.c $(CONFIG_H) $(CPLUS_TREE_H) \
   cp-parse.h cp-input.c flags.h
cp-decl.o : cp-decl.c $(CONFIG_H) $(CPLUS_TREE_H) flags.h \
  cp-parse.h cp-decl.h stack.h
cp-decl2.o : cp-decl2.c $(CONFIG_H) $(CPLUS_TREE_H) flags.h \
  cp-parse.h cp-decl.h
cp-type2.o : cp-type2.c $(CONFIG_H) $(CPLUS_TREE_H) flags.h
cp-typeck.o : cp-typeck.c $(CONFIG_H) $(CPLUS_TREE_H) flags.h
cp-class.o : cp-class.c $(CONFIG_H) $(CPLUS_TREE_H) stack.h \
    cp-class.h flags.h
cp-call.o : cp-call.c $(CONFIG_H) $(CPLUS_TREE_H) stack.h cp-class.h \
    flags.h
cp-init.o : cp-init.c $(CONFIG_H) $(CPLUS_TREE_H) flags.h
cp-method.o : cp-method.c $(CONFIG_H) $(CPLUS_TREE_H)
cp-cvt.o : cp-cvt.c $(CONFIG_H) $(CPLUS_TREE_H)
cp-search.o : cp-search.c $(CONFIG_H) $(CPLUS_TREE_H) stack.h flags.h
cp-tree.o : cp-tree.c $(CONFIG_H) $(CPLUS_TREE_H) flags.h
cp-ptree.o : cp-ptree.c $(CONFIG_H) $(CPLUS_TREE_H)
cp-gc.o : cp-gc.c $(CONFIG_H) $(CPLUS_TREE_H) flags.h
cp-except.o : cp-except.c $(CONFIG_H) $(CPLUS_TREE_H) flags.h
cp-expr.o : cp-expr.c $(CONFIG_H) $(CPLUS_TREE_H) $(RTL_H) flags.h \
  expr.h insn-codes.h
cp-edsel.o : cp-edsel.c $(CONFIG_H) $(CPLUS_TREE_H) stack.h flags.h
cp-xref.o : cp-xref.c $(CONFIG_H) $(CPLUS_TREE_H)
cp-pt.o : cp-pt.c $(CONFIG_H) $(CPLUS_TREE_H) cp-decl.h cp-parse.h

# Objectionable C language specific files.

objc-parse.o : objc-parse.c $(TREE_H) c-parse.h \
   c-tree.h input.h flags.h objc-actions.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -c objc-parse.c
objc-parse.c : objc-parse.y
	$(BISON) $(BISONFLAGS) objc-parse.y -o $@

objc-actions.o : objc-actions.c $(TREE_H) c-tree.h c-parse.h \
   flags.h objc-actions.h

# A file used by all variants of C.

c-common.o : c-common.c $(TREE_H) c-tree.h c-parse.h flags.h

# Language-independent files.

gcc.o: gcc.c gvarargs.h obstack.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -c gcc.c

dumpvers: dumpvers.c

version.o: version.c
obstack.o: obstack.c

tree.o : tree.c $(CONFIG_H) $(TREE_H) gvarargs.h flags.h function.h
print-tree.o : print-tree.c $(CONFIG_H) $(TREE_H)
stor-layout.o : stor-layout.c $(CONFIG_H) $(TREE_H) function.h
fold-const.o : fold-const.c $(CONFIG_H) $(TREE_H) flags.h 
toplev.o : toplev.c $(CONFIG_H) $(TREE_H) $(RTL_H) flags.h input.h insn-attr.h

rtl.o : rtl.c $(CONFIG_H) $(RTL_H)

rtlanal.o : rtlanal.c $(CONFIG_H) $(RTL_H)

varasm.o : varasm.c $(CONFIG_H) $(TREE_H) $(RTL_H) flags.h \
   insn-codes.h expr.h hard-reg-set.h regs.h
function.o : function.c $(CONFIG_H) $(RTL_H) $(TREE_H) flags.h function.h  \
   insn-flags.h insn-codes.h expr.h regs.h hard-reg-set.h insn-config.h \
   recog.h output.h
stmt.o : stmt.c $(CONFIG_H) $(RTL_H) $(TREE_H) flags.h function.h  \
   insn-flags.h insn-config.h insn-codes.h hard-reg-set.h expr.h loop.h recog.h
expr.o : expr.c $(CONFIG_H) $(RTL_H) $(TREE_H) gvarargs.h flags.h function.h  \
   insn-flags.h insn-codes.h expr.h insn-config.h recog.h output.h typeclass.h
calls.o : calls.c $(CONFIG_H) $(RTL_H) $(TREE_H) flags.h expr.h insn-flags.h
expmed.o : expmed.c $(CONFIG_H) $(RTL_H) $(TREE_H) flags.h  \
   insn-flags.h insn-config.h insn-codes.h expr.h recog.h
explow.o : explow.c $(CONFIG_H) $(RTL_H) $(TREE_H) flags.h hard-reg-set.h \
   insn-config.h expr.h recog.h insn-flags.h insn-codes.h
optabs.o : optabs.c $(CONFIG_H) $(RTL_H) $(TREE_H) flags.h  \
   insn-flags.h insn-config.h insn-codes.h expr.h recog.h
# symout.o : symout.c $(CONFIG_H) $(TREE_H) $(RTL_H) symseg.h gdbfiles.h
dbxout.o : dbxout.c $(CONFIG_H) $(TREE_H) $(RTL_H) flags.h regs.h \
    insn-config.h
sdbout.o : sdbout.c $(CONFIG_H) $(TREE_H) $(RTL_H) gsyms.h
dwarfout.o : dwarfout.c $(CONFIG_H) $(TREE_H) $(RTL_H) flags.h

emit-rtl.o : emit-rtl.c $(CONFIG_H) $(RTL_H) gvarargs.h function.h  \
   regs.h insn-config.h real.h expr.h
getpwd.o : getpwd.c $(CONFIG_H)

integrate.o : integrate.c $(CONFIG_H) $(RTL_H) $(TREE_H) flags.h integrate.h \
   insn-flags.h insn-config.h expr.h real.h function.h

jump.o : jump.c $(CONFIG_H) $(RTL_H) flags.h hard-reg-set.h regs.h \
   insn-config.h insn-flags.h expr.h real.h
stupid.o : stupid.c $(CONFIG_H) $(RTL_H) regs.h hard-reg-set.h flags.h

cse.o : cse.c $(CONFIG_H) $(RTL_H) regs.h hard-reg-set.h flags.h real.h \
   insn-config.h recog.h
loop.o : loop.c $(CONFIG_H) $(RTL_H) flags.h loop.h \
   insn-config.h insn-flags.h regs.h hard-reg-set.h recog.h expr.h real.h
unroll.o : unroll.c $(CONFIG_H) $(RTL_H) insn-config.h integrate.h regs.h \
   flags.h expr.h loop.h
flow.o : flow.c $(CONFIG_H) $(RTL_H) flags.h insn-config.h \
   basic-block.h regs.h hard-reg-set.h output.h
combine.o : combine.c $(CONFIG_H) $(RTL_H) gvarargs.h flags.h  \
   insn-config.h insn-flags.h insn-codes.h insn-attr.h regs.h expr.h \
   basic-block.h recog.h real.h
regclass.o : regclass.c $(CONFIG_H) $(RTL_H) hard-reg-set.h flags.h \
   basic-block.h regs.h insn-config.h recog.h 
local-alloc.o : local-alloc.c $(CONFIG_H) $(RTL_H) flags.h basic-block.h \
   regs.h hard-reg-set.h insn-config.h recog.h output.h
global-alloc.o : global-alloc.c $(CONFIG_H) $(RTL_H) flags.h  \
   basic-block.h regs.h hard-reg-set.h insn-config.h output.h

reload.o : reload.c $(CONFIG_H) $(RTL_H) flags.h \
   reload.h recog.h hard-reg-set.h insn-config.h regs.h real.h
reload1.o : reload1.c $(CONFIG_H) $(RTL_H) flags.h  \
   reload.h regs.h hard-reg-set.h insn-config.h insn-flags.h basic-block.h \
   recog.h output.h
caller-save.o : caller-save.c $(CONFIG_H) $(RTL_H) flags.h \
   reload.h regs.h hard-reg-set.h insn-config.h basic-block.h recog.h
reorg.o : reorg.c $(CONFIG_H) $(RTL_H) conditions.h hard-reg-set.h \
   basic-block.h regs.h insn-config.h insn-attr.h insn-flags.h recog.h \
   flags.h output.h
sched.o : sched.c $(CONFIG_H) $(RTL_H) basic-block.h regs.h hard-reg-set.h \
   flags.h insn-config.h insn-attr.h
final.o : final.c $(CONFIG_H) $(RTL_H) gvarargs.h flags.h regs.h \
   recog.h conditions.h \
   insn-config.h insn-attr.h real.h output.h hard-reg-set.h
recog.o : recog.c $(CONFIG_H) $(RTL_H)  \
   regs.h recog.h hard-reg-set.h flags.h insn-config.h insn-attr.h \
   insn-flags.h insn-codes.h real.h
reg-stack.o : reg-stack.c $(CONFIG_H) $(RTL_H) $(TREE_H) \
   regs.h hard-reg-set.h flags.h

aux-output.o : aux-output.c $(CONFIG_H) \
   $(RTL_H) regs.h hard-reg-set.h real.h insn-config.h conditions.h \
   insn-flags.h output.h insn-attr.h

# Remake cpp and protoize.

# Making the preprocessor
cpp: cccp.o cexp.o version.o $(LIBDEPS)
	$(CC) $(LDFLAGS) -o cpp cccp.o cexp.o version.o $(LIBS)
cexp.o: cexp.c
	$(CC) $(CPPFLAGS) $(INCLUDES) -c cexp.c
cexp.c: cexp.y
	$(BISON) -o cexp.c cexp.y
cccp.o: cccp.c pcp.h version.c
	$(CC) $(CPPFLAGS) $(INCLUDES) \
	-c cccp.c

proto: config.status protoize unprotoize SYSCALLS.c.X protoize.1 unprotoize.1

protoize: protoize.o getopt.o getopt1.o getpwd.o $(MALLOC)
	gcc -B./ $(GCC_CFLAGS) $(LDFLAGS) protoize.o getopt.o getopt1.o \
	  $(MALLOC) -o $@
protoize.o:	protoize.c cc1 cpp getopt.h
	gcc -B./ -c $(GCC_CFLAGS) $(CPPFLAGS) $(INCLUDES) \
          -DGCC_INCLUDE_DIR=\"$(libsubdir)/include\" \
          -DGPLUSPLUS_INCLUDE_DIR=\"$(libsubdir)/g++-include\" \
          -DCROSS_INCLUDE_DIR=\"$(libsubdir)/sys-include\" \
	  -DSTD_PROTO_DIR=\"$(libsubdir)\" \
	  protoize.c -I$(srcdir)

unprotoize: unprotoize.o getopt.o getopt1.o getpwd.o $(MALLOC)
	gcc -B./ $(GCC_CFLAGS) $(LDFLAGS) unprotoize.o getopt.o getopt1.o \
	  $(MALLOC) -o $@
unprotoize.o:	protoize.c cc1 cpp getopt.h
	gcc -B./ -c $(GCC_CFLAGS) $(CPPFLAGS) $(INCLUDES) \
          -DGCC_INCLUDE_DIR=\"$(libsubdir)/include\" \
          -DGPLUSPLUS_INCLUDE_DIR=\"$(libsubdir)/g++-include\" \
          -DCROSS_INCLUDE_DIR=\"$(libsubdir)/sys-include\" \
	  -DSTD_PROTO_DIR=\"$(libsubdir)\" \
	  -DUNPROTOIZE protoize.c -I$(srcdir) -o $@

getopt.o: getopt.c getopt.h cc1 cpp
	gcc -B./ -c $(GCC_CFLAGS) $(CPPFLAGS) $(INCLUDES) getopt.c
getopt1.o: getopt1.c getopt.h cc1 cpp
	gcc -B./ -c $(GCC_CFLAGS) $(CPPFLAGS) $(INCLUDES) getopt1.c

protoize.1:	proto-man ./cpp
	./cpp -traditional proto-man \
		| grep -v '^#' \
			| awk 'NF > 0 {print}' > protoize.1

unprotoize.1:	proto-man ./cpp
	./cpp -traditional -DUNPRO proto-man \
		| grep -v '^#' \
			| awk 'NF > 0 {print}' > unprotoize.1

SYSCALLS.c : $(srcdir)/sys-types.h $(srcdir)/sys-protos.h
	cat $(srcdir)/sys-types.h $(srcdir)/sys-protos.h >$@

# This info describes the target machine, so compile with GCC just built.
SYSCALLS.c.X:	SYSCALLS.c $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) \
	  -aux-info $@ -S -o /dev/null SYSCALLS.c

test-protoize:
	-rm -f tmp-protoize.*
	cp protoize.c tmp-protoize.c
	chmod u+w tmp-protoize.c
	./unprotoize -N -c "-B./ -Wall -Wwrite-strings $(CFLAGS)" tmp-protoize.c
	./protoize -N -B ./ -c "-B./ -Wall -Wwrite-strings $(CFLAGS)" tmp-protoize.c
	@echo Expect exactly one one line difference for visit_each_hash_node.
	-diff protoize.c tmp-protoize.c
	-rm -f tmp-protoize.*

force:


# The following pair of rules has this effect:
# genconfig is run only if the md has changed since genconfig was last run;
# but the file insn-config.h is touched only when its contents actually change.

# Each of the other insn-* files is handled by a similar pair of rules.

# Each of the insn-*.[ch] rules has a semicolon at the end,
# for otherwise the system Make on SunOS 4.1 never tries
# to recompile insn-*.o.

insn-config.h: tmp-conf.h
tmp-conf.h: md genconfi.exe
	genconfi md > tmp-conf.h
	updt tmp-conf.h insn-config.h

insn-flags.h: tmp-flags.h
tmp-flags.h: md genflags.exe
	genflags md > tmp-flag.h
	updt tmp-flag.h insn-flags.h

insn-codes.h: tmp-code.h
tmp-code.h: md gencodes.exe
	gencodes md > tmp-code.h
	updt tmp-code.h insn-codes.h

insn-emit.o : insn-emit.c $(CONFIG_H) $(RTL_H) expr.h real.h output.h \
  insn-config.h insn-flags.h insn-codes.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -c insn-emit.c

insn-emit.c: md genemit.exe
	genemit md > tmp-emit.c
	updt tmp-emit.c insn-emit.c

insn-recog.o : insn-recog.c $(CONFIG_H) $(RTL_H) insn-config.h recog.h \
  real.h output.h flags.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -c insn-recog.c

insn-recog.c: tmp-reco.c
tmp-reco.c: md genrecog.exe
	genrecog md > tmp-reco.c
	updt tmp-reco.c insn-recog.c

insn-extract.o : insn-extract.c $(CONFIG_H) $(RTL_H)
	$(CC) $(CPPFLAGS) $(INCLUDES) -c insn-extract.c

insn-extract.c: tmp-extr.c
tmp-extr.c: md genextra.exe
	genextra md > tmp-extr.c
	updt tmp-extr.c insn-extract.c

insn-peep.o : insn-peep.c $(CONFIG_H) $(RTL_H) regs.h output.h real.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -c insn-peep.c

insn-peep.c: tmp-peep.c
tmp-peep.c: md genpeep.exe
	genpeep md > tmp-peep.c
	updt tmp-peep.c insn-peep.c

insn-attrtab.o : insn-attrtab.c $(CONFIG_H) $(RTL_H) regs.h real.h output.h \
     insn-attr.h insn-config.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -c insn-attrtab.c

insn-attr.h: tmp-attr.h
tmp-attr.h: md genattr.exe
	genattr md > tmp-attr.h
	updt tmp-attr.h insn-attr.h

insn-attrtab.c: tmp-attr.c
tmp-attr.c: md genattrt.exe
	genattrt md > tmp-attr.c
	updt tmp-attr.c insn-attrtab.c

insn-output.o : insn-output.c $(CONFIG_H) $(RTL_H) regs.h real.h conditions.h \
    hard-reg-set.h insn-config.h insn-flags.h insn-attr.h output.h recog.h \
    insn-codes.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -c insn-output.c

insn-output.c: tmp-outp.c
tmp-outp.c: md genoutpu.exe
	genoutpu md > tmp-outp.c
	updt tmp-outp.c insn-output.c

# Compile the programs that generate insn-* from the machine description.
# They are compiled with $(CC), and associated libraries,
# since they need to run on this machine
# even if GCC is being compiled to run on some other machine.

# $(CONFIG_H) is omitted from the deps of the gen*.o
# because these programs don't really depend on anything 
# about the target machine.  They do depend on config.h itself,
# since that describes the host machine.

genconfi.exe : genconfig.o $(RTL) $(LIBDEPS) $(OBSTACK)
	$(CC) $(LDFLAGS) -o genconfi.exe \
	  genconfig.o $(RTL) $(OBSTACK) $(LIBS)

genconfig.o : genconfig.c $(RTL_H) config.h
	$(CC) -c $(CPPFLAGS) $(INCLUDES)  genconfig.c

genflags.exe : genflags.o $(RTL) $(LIBDEPS) $(OBSTACK)
	$(CC) $(LDFLAGS) -o genflags.exe \
	 genflags.o $(RTL) $(OBSTACK) $(LIBS)

genflags.o : genflags.c $(RTL_H) config.h
	$(CC) -c $(CPPFLAGS) $(INCLUDES)  genflags.c

gencodes.exe : gencodes.o $(RTL) $(LIBDEPS) $(OBSTACK)
	$(CC) $(LDFLAGS) -o gencodes.exe \
	 gencodes.o $(RTL) $(OBSTACK) $(LIBS)

gencodes.o : gencodes.c $(RTL_H) config.h
	$(CC) -c $(CPPFLAGS) $(INCLUDES)  gencodes.c

genemit.exe : genemit.o $(RTL) $(LIBDEPS) $(OBSTACK)
	$(CC) $(LDFLAGS) -o genemit.exe \
	 genemit.o $(RTL) $(OBSTACK) $(LIBS)

genemit.o : genemit.c $(RTL_H) config.h
	$(CC) -c $(CPPFLAGS) $(INCLUDES)  genemit.c

genrecog.exe : genrecog.o $(RTL) $(LIBDEPS) $(OBSTACK)
	$(CC) $(LDFLAGS) -o genrecog.exe \
	 genrecog.o $(RTL) $(OBSTACK) $(LIBS)

genrecog.o : genrecog.c $(RTL_H) config.h
	$(CC) -c $(CPPFLAGS) $(INCLUDES)  genrecog.c

genextra.exe : genextract.o $(RTL) $(LIBDEPS) $(OBSTACK)
	$(CC) $(LDFLAGS) -o genextra.exe \
	 genextract.o $(RTL) $(OBSTACK) $(LIBS)

genextract.o : genextract.c $(RTL_H) config.h
	$(CC) -c $(CPPFLAGS) $(INCLUDES)  genextract.c

genpeep.exe : genpeep.o $(RTL) $(LIBDEPS) $(OBSTACK)
	$(CC) $(LDFLAGS) -o genpeep.exe \
	 genpeep.o $(RTL) $(OBSTACK) $(LIBS)

genpeep.o : genpeep.c $(RTL_H) config.h
	$(CC) -c $(CPPFLAGS) $(INCLUDES)  genpeep.c

genattr.exe : genattr.o $(RTL) $(LIBDEPS) $(OBSTACK)
	$(CC) $(LDFLAGS) -o genattr.exe \
	 genattr.o $(RTL) $(OBSTACK) $(LIBS)

genattr.o : genattr.c $(RTL_H) config.h
	$(CC) -c $(CPPFLAGS) $(INCLUDES)  genattr.c

genattrt.exe : genattrtab.o $(RTL) $(RTLANAL) $(LIBDEPS) $(OBSTACK)
	$(CC) $(LDFLAGS) -o genattrt.exe \
	 genattrtab.o $(RTL) $(RTLANAL) $(OBSTACK) $(LIBS)

genattrtab.o : genattrtab.c $(RTL_H) config.h insn-config.h
	$(CC) -c $(CPPFLAGS) $(INCLUDES)  genattrtab.c

genoutpu.exe : genoutput.o $(RTL) $(LIBDEPS) $(OBSTACK)
	$(CC) $(LDFLAGS) -o genoutpu.exe \
	 genoutput.o $(RTL) $(OBSTACK) $(LIBS)

genoutput.o : genoutput.c $(RTL_H) config.h
	$(CC) -c $(CPPFLAGS) $(INCLUDES)  genoutput.c

print-rtl.o: print-rtl.c
