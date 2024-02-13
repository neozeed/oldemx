/* objdump.c -- changed for emx by Eberhard Mattes -- Jan 1992 */

/* objdump -- dump information about an object file.
   Copyright (C) 1988, Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/*
 * objdump
 * 
 * dump information about an object file.  Until there is other documentation,
 * refer to the manual page dump(1) in the system 5 program's reference manual
 */
#include <stdio.h>
#include <stdlib.h>
#include "getopt.h"

#ifndef COFF_ENCAPSULATE
#include <a_out.h>
#else
#include "a.out.encap.h"
#endif

#define HEADER_SEEK(f) _fseek_hdr(f)
static long hdr_pos;

char *xmalloc();
int nsyms;
struct nlist *symtbl;
char *strtbl;
int strsize;
char *program_name;

read_symbols (execp, f)
struct exec *execp;
FILE *f;
{
	int i;
	struct nlist *sp;
	if (symtbl)
		return;
	nsyms = execp->a_syms / sizeof (struct nlist);
	if (nsyms == 0)
		return;

	symtbl = (struct nlist *)xmalloc (nsyms * sizeof (struct nlist));

    fseek (f, N_STROFF(*execp) + hdr_pos, 0);
	if (fread ((char *)&strsize, sizeof strsize, 1, f) != 1) {
		fprintf (stderr, "%s: can not read string table size\n",
			 program_name);
		exit (1);
	}
	strtbl = xmalloc (strsize);
    fseek (f, N_STROFF (*execp) + hdr_pos, 0);
	if (fread (strtbl, 1, strsize, f) != strsize) {
		fprintf (stderr, "%s: error reading string table\n",
			 program_name);
		exit (1);
	}

    fseek (f, N_SYMOFF (*execp) + hdr_pos, 0);
	if (fread ((char *)symtbl, sizeof (struct nlist), nsyms, f) != nsyms) {
		fprintf (stderr, "%s: error reading symbol table\n",
			 program_name);
		exit (1);
	}

	for (i = 0, sp = symtbl; i < nsyms; i++, sp++) {
		if (sp->n_un.n_strx == 0)
			sp->n_un.n_name = "";
		else if (sp->n_un.n_strx < 0 || sp->n_un.n_strx > strsize)
			sp->n_un.n_name = "<bad string table index>";
		else
			sp->n_un.n_name = strtbl + sp->n_un.n_strx;
	}
}

free_symbols ()
{
	if (symtbl)
		free (symtbl);
	symtbl = NULL;
	if (strtbl)
		free (strtbl);
	strtbl = NULL;
}


usage ()
{
	fprintf (stderr, "\
Usage: %s [-hnrt] [+header] [+nstuff] [+reloc] [+symbols] file...\n",
		 program_name);
	exit (1);
}

int hflag;
int nflag;
int rflag;
int tflag;

/* Size of a page.  Required by N_DATADDR in a.out.gnu.h [VAX].  */
int page_size;

main (argc, argv)
char **argv;
{
	int c;
	extern char *optarg;
	extern int optind;
	int seenflag = 0;
	int ind = 0;
	static struct option long_options[] = 
	  {
	    {"symbols",   0, &tflag, 1},
	    {"reloc",  0, &rflag, 1},
	    {"nstuff", 0, &nflag, 1},
	    {"header", 0, &hflag, 1},
	    {NULL, 0, NULL, 0}
	  };

    _wildcard (&argc, &argv);
	page_size = getpagesize ();

	program_name = argv[0];
		 		 
	while ((c = getopt_long (argc, argv, "hnrt", long_options, &ind))
 		      != EOF) {
		seenflag = 1;
		switch (c) {
		case  0 : break; /* we've been given a long option */
		case 't': tflag = 1; break;
		case 'r': rflag = 1; break;
		case 'n': nflag = 1; break;
		case 'h': hflag = 1; break;
		default:
			usage ();
		}
	}

	if (seenflag == 0 || optind == argc)
		usage ();

	while (optind < argc)
		doit (argv[optind++]);
}

doit (name)
char *name;
{
	FILE *f;
	struct exec exec;
	printf ("%s:\n", name);
        f = fopen (name, "rb");
	if (f == NULL) {
		fprintf (stderr, "%s: can not open ", program_name);
		perror (name);
		return;
	}
#ifdef HEADER_SEEK
	HEADER_SEEK (f);
#endif
	hdr_pos = ftell (f);
	if (fread ((char *)&exec, sizeof exec, 1, f) != 1) {
		fprintf (stderr, "%s: can not read header for %s\n",
			 program_name, name);
		return;
	}

	if (N_BADMAG (exec)) {
		fprintf (stderr, "%s: %s is not an object file\n",
			 program_name, name);
		return;
	}

	if (hflag)
		dump_header (&exec);

	if (nflag)
		dump_nstuff (&exec);

	if (tflag)
		dump_sym (&exec, f);

	if (rflag)
		dump_reloc (&exec, f);

	free_symbols ();

}

dump_header (execp)
struct exec *execp;
{
	int x;

#if defined (__GNU_EXEC_MACROS__) && !defined (__STRUCT_EXEC_OVERRIDE__)
	printf ("magic: 0x%x (%o) ", N_MAGIC(*execp), N_MAGIC(*execp));
	printf ("machine type: %d ", N_MACHTYPE(*execp));
	printf ("flags: 0x%x ", N_FLAGS(*execp));
#else /* non-gnu struct exec.  */
	printf ("magic: 0x%x (%o) ", execp->a_magic, execp->a_magic);
#endif /* non-gnu struct exec.  */
	printf ("text 0x%x ", execp->a_text);
	printf ("data 0x%x ", execp->a_data);
	printf ("bss 0x%x\n", execp->a_bss);
	printf ("nsyms %d", execp->a_syms / sizeof (struct nlist));
	x = execp->a_syms % sizeof (struct nlist);
	if (x) 
		printf (" (+ %d bytes)", x);
	printf (" entry 0x%x ", execp->a_entry);
	printf ("trsize 0x%x ", execp->a_trsize);
	printf ("drsize 0x%x\n", execp->a_drsize);
}

dump_nstuff (execp)
struct exec *execp;
{
	printf ("N_BADMAG %d\n", N_BADMAG (*execp));
	printf ("N_TXTOFF 0x%x\n", N_TXTOFF (*execp));
	printf ("N_SYMOFF 0x%x\n", N_SYMOFF (*execp));
	printf ("N_STROFF 0x%x\n", N_STROFF (*execp));
	printf ("N_TXTADDR 0x%x\n", N_TXTADDR (*execp));
	printf ("N_DATADDR 0x%x\n", N_DATADDR (*execp));
}

dump_sym (execp, f)
struct exec *execp;
FILE *f;
{
	int i;
	struct nlist *sp;

	read_symbols (execp, f);
	if (nsyms == 0) {
		printf ("no symbols\n");
		return;
	}

	printf ("%3s: %4s %5s %4s %8s\n",
		"#", "type", "other", "desc", "val");
	for (i = 0, sp = symtbl; i < nsyms; i++, sp++) {
		printf ("%3d: %4x %5x %4x %8x %s\n",
			i,
			sp->n_type & 0xff,
			sp->n_other & 0xff,
			sp->n_desc & 0xffff,
			sp->n_value,
			sp->n_un.n_name);
	}
}

dump_reloc (execp, f)
struct exec *execp;
FILE *f;
{
	read_symbols (execp, f);
	if (execp->a_trsize) {
		printf ("text reloc\n");
        dump_reloc1 (execp, f, N_TRELOFF (*execp) + hdr_pos, execp->a_trsize);
	}
	if (execp->a_drsize) {
		printf ("data reloc\n");
        dump_reloc1 (execp, f, N_DRELOFF (*execp) + hdr_pos, execp->a_drsize);
	}
}

dump_reloc1 (execp, f, off, size)
struct exec *execp;
FILE *f;
{
	int nreloc;
	struct relocation_info reloc;
	int i;

	nreloc = size / sizeof (struct relocation_info);

	printf ("%3s: %3s %8s %4s\n", "#", "len", "adr", "sym");
	fseek (f, off, 0);
	for (i = 0; i < nreloc; i++) {
		if (fread ((char *)&reloc, sizeof reloc, 1, f) != 1) {
			fprintf (stderr, "%s: error reading reloc\n",
				 program_name);
			return;
		}
		printf ("%3d: %3d %8x ", i, 1 << reloc.r_length,
			reloc.r_address);
		
		if (reloc.r_extern) {
			printf ("%4d ", reloc.r_symbolnum);
			if (reloc.r_symbolnum < nsyms)
				printf ("%s ",
					symtbl[reloc.r_symbolnum].n_un.n_name);
		} else {
			printf ("     ");
			switch (reloc.r_symbolnum & ~N_EXT) {
			case N_TEXT: printf (".text "); break;
			case N_DATA: printf (".data "); break;
			case N_BSS: printf (".bss "); break;
			case N_ABS: printf (".abs "); break;
			default: printf ("base %x ", reloc.r_symbolnum); break;
			}
		}
		if (reloc.r_pcrel) printf ("PCREL ");
#if 0
		if (reloc.r_pad) printf ("PAD %x ", reloc.r_pad);
#endif
		printf ("\n");
	}
}

/* Allocate `n' bytes of memory dynamically, with error checking.  */

char *
xmalloc (n)
     unsigned n;
{
  char *p;

  p = malloc (n);
  if (p == 0)
    {
      fprintf (stderr, "%s: virtual memory exhausted\n", program_name);
      exit (1);
    }
  return p;
}
