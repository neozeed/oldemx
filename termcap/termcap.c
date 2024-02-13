/* termcap.c -- changed for emx by Eberhard Mattes -- Jan 1992 */

/* GNU termcap */

/* Work-alike for termcap, plus extra features.
   Copyright (C) 1985, 1986 Free Software Foundation, Inc.

		       NO WARRANTY

  BECAUSE THIS PROGRAM IS LICENSED FREE OF CHARGE, WE PROVIDE ABSOLUTELY
NO WARRANTY, TO THE EXTENT PERMITTED BY APPLICABLE STATE LAW.  EXCEPT
WHEN OTHERWISE STATED IN WRITING, FREE SOFTWARE FOUNDATION, INC,
RICHARD M. STALLMAN AND/OR OTHER PARTIES PROVIDE THIS PROGRAM "AS IS"
WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY
AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE PROGRAM PROVE
DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR
CORRECTION.

 IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW WILL RICHARD M.
STALLMAN, THE FREE SOFTWARE FOUNDATION, INC., AND/OR ANY OTHER PARTY
WHO MAY MODIFY AND REDISTRIBUTE THIS PROGRAM AS PERMITTED BELOW, BE
LIABLE TO YOU FOR DAMAGES, INCLUDING ANY LOST PROFITS, LOST MONIES, OR
OTHER SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
USE OR INABILITY TO USE (INCLUDING BUT NOT LIMITED TO LOSS OF DATA OR
DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY THIRD PARTIES OR
A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS) THIS
PROGRAM, EVEN IF YOU HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
DAMAGES, OR FOR ANY CLAIM BY ANY OTHER PARTY.

		GENERAL PUBLIC LICENSE TO COPY

  1. You may copy and distribute verbatim copies of this source file
as you receive it, in any medium, provided that you conspicuously and
appropriately publish on each copy a valid copyright notice "Copyright
(C) 1986 Free Software Foundation, Inc."; and include following the
copyright notice a verbatim copy of the above disclaimer of warranty
and of this License.  You may charge a distribution fee for the
physical act of transferring a copy.

  2. You may modify your copy or copies of this source file or
any portion of it, and copy and distribute such modifications under
the terms of Paragraph 1 above, provided that you also do the following:

    a) cause the modified files to carry prominent notices stating
    that you changed the files and the date of any change; and

    b) cause the whole of any work that you distribute or publish,
    that in whole or in part contains or is a derivative of this
    program or any part thereof, to be licensed at no charge to all
    third parties on terms identical to those contained in this
    License Agreement (except that you may choose to grant more extensive
    warranty protection to some or all third parties, at your option).

    c) You may charge a distribution fee for the physical act of
    transferring a copy, and you may at your option offer warranty
    protection in exchange for a fee.

Mere aggregation of another unrelated program with this program (or its
derivative) on a volume of a storage or distribution medium does not bring
the other program under the scope of these terms.

  3. You may copy and distribute this program (or a portion or derivative
of it, under Paragraph 2) in object code or executable form under the terms
of Paragraphs 1 and 2 above provided that you also do one of the following:

    a) accompany it with the complete corresponding machine-readable
    source code, which must be distributed under the terms of
    Paragraphs 1 and 2 above; or,

    b) accompany it with a written offer, valid for at least three
    years, to give any third party free (except for a nominal
    shipping charge) a complete machine-readable copy of the
    corresponding source code, to be distributed under the terms of
    Paragraphs 1 and 2 above; or,

    c) accompany it with the information you received as to where the
    corresponding source code may be obtained.  (This alternative is
    allowed only for noncommercial distribution and only if you
    received the program in object code or executable form alone.)

For an executable file, complete source code means all the source code for
all modules it contains; but, as a special exception, it need not include
source code for modules which are standard libraries that accompany the
operating system on which the executable file runs.

  4. You may not copy, sublicense, distribute or transfer this program
except as expressly provided under this License Agreement.  Any attempt
otherwise to copy, sublicense, distribute or transfer this program is void and
your rights to use the program under this License agreement shall be
automatically terminated.  However, parties who have received computer
software programs from you with this License Agreement will not have
their licenses terminated so long as such parties remain in full compliance.

  5. If you wish to incorporate parts of this program into other free
programs whose distribution conditions are different, write to the Free
Software Foundation at 675 Mass Ave, Cambridge, MA 02139.  We have not yet
worked out a simple rule that can be stated here, but we will often permit
this.  We will be guided by the two goals of preserving the free status of
all derivatives of our free software and of promoting the sharing and reuse of
software.


In other words, you are welcome to use, share and improve this program.
You are forbidden to forbid anyone else to use, share and improve
what you give them.   Help stamp out software-hoarding!  */



/* BUFSIZE is the initial size allocated for the buffer
   for reading the termcap file.
   It is not a limit.
   Make it large normally for speed.
   Make it variable when debugging, so can exercise
   increasing the space dynamically.  */

#ifdef emacs
#include "config.h"
#endif

#ifndef BUFSIZE
#ifdef DEBUG
#define BUFSIZE bufsize

int bufsize = 128;
#else
#define BUFSIZE 2048
#endif
#endif

#ifdef EMX
#include "termcap.h"
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <io.h>
#endif


/*em: moved up */

/* Finding the termcap entry in the termcap data base */

struct buffer
  {
    char *beg;
    int size;
    char *ptr;
    int ateof;
    int full;
  };


/* Forward declarations of static functions */

static void *xmalloc (int);
static void *xrealloc (void *, int);
static char *find_capability (char *, char *);
static char *tgetst1 (char *, char **);
static int scan_file (char *, int, struct buffer *);
static char *gobble_line (int, struct buffer *, char *);
static int compare_contin (char *, char *);
static int name_match (char *, char *);


#ifndef emacs
static
void memory_out ()
{
  write (2, "Virtual memory exhausted\n", 25);
  exit (1);
}

static void *
xmalloc (size)
     int size;
{
  void *tem = malloc (size);
  if (!tem)
    memory_out ();
  return tem;
}

static void *
xrealloc (ptr, size)
     void *ptr;
     int size;
{
  void *tem = realloc (ptr, size);
  if (!tem)
    memory_out ();
  return tem;
}
#endif /* not emacs */

/* Looking up capabilities in the entry already found */

/* The pointer to the data made by tgetent is left here
   for tgetnum, tgetflag and tgetstr to find.  */

static char *term_entry;

/* This is the main subroutine that is used to search
   an entry for a particular capability */

static char *
find_capability (bp, cap)
     register char *bp, *cap;
{
  for (; *bp; bp++)
    if (bp[0] == ':'
	&& bp[1] == cap[0]
	&& bp[2] == cap[1])
      return &bp[4];
  return 0;
}

int
tgetnum (cap)
     char *cap;
{
  register char *ptr = find_capability (term_entry, cap);
  if (!ptr || ptr[-1] != '#')
    return -1;
  return atoi (ptr);
}

int
tgetflag (cap)
     char *cap;
{
  register char *ptr = find_capability (term_entry, cap);
  return 0 != ptr && ptr[-1] == ':';
}

/* Look up a string-valued capability `cap'.
   If `area' is nonzero, it points to a pointer to a block in which
   to store the string.  That pointer is advanced over the space used.
   If `area' is zero, space is allocated with `malloc'.  */

char *
tgetstr (cap, area)
     char *cap;
     char **area;
{
  register char *ptr = find_capability (term_entry, cap);
  if (!ptr || (ptr[-1] != '=' && ptr[-1] != '~'))
    return 0;
  return tgetst1 (ptr, area);
}

/* Table, indexed by a character in range 0100 to 0140 with 0100 subtracted,
   gives meaning of character following \, or a space if no special meaning.
   Eight characters per line within the string.  */

static char esctab[]
  = " \007\010  \033\014 \
      \012 \
  \015 \011 \013 \
        ";

/* Given a pointer to a string value inside a termcap entry (`ptr'),
   copy the value and process \ and ^ abbreviations.
   Copy into block that *area points to,
   or to newly allocated storage if area is 0.  */

static char *
tgetst1 (ptr, area)
     char *ptr;
     char **area;
{
  register char *p, *r;
  register int c;
  register int size;
  char *ret;
  register int c1;

  if (!ptr)
    return 0;

  /* `ret' gets address of where to store the string */
  if (!area)
    {
      /* Compute size of block needed (may overestimate) */
      p = ptr;
      while ((c = *p++) && c != ':' && c != '\n');
      ret = (char *) xmalloc (p - ptr + 1);
    }
  else
    ret = *area;

  /* Copy the string value, stopping at null or colon.  */
  /* Also process ^ and \ abbreviations.  */
  p = ptr;
  r = ret;
  while ((c = *p++) && c != ':' && c != '\n')
    {
      if (c == '^')
	c = *p++ & 037;
      else if (c == '\\')
	{
	  c = *p++;
	  if (c >= '0' && c <= '7')
	    {
	      c -= '0';
	      size = 0;

	      while (++size < 3 && (c1 = *p) >= '0' && c1 <= '7')
		{
		  c *= 8;
		  c += c1 - '0';
		  p++;
		}
	    }
	  else if (c >= 0100 && c < 0200)
	    {
	      c1 = esctab[(c & ~040) - 0100];
	      if (c1 != ' ')
		c = c1;
	    }
	}
      *r++ = (char) c;
    }
  *r = 0;
  /* Update *area */
  if (area)
    *area = r + 1;
  return ret;
}

/* Outputting a string with padding */

short ospeed;
char PC;

/* Actual baud rate if positive;
   - baud rate / 100 if negative.  */

static short speeds[] =
  {
#ifdef VMS
    0, 50, 75, 110, 134, 150, -3, -6, -12, -18,
    -20, -24, -36, -48, -72, -96, -192
#else /* not VMS */
    0, 50, 75, 110, 135, 150, -2, -3, -6, -12,
    -18, -24, -48, -96, -192, -384
#endif /* not VMS */
  };

void tputs (string, nlines, outfun)
     register char *string;
     int nlines;
     register int (*outfun) (int);
{
  register int padcount = 0;

  if (string == (char *) 0)
    return;
  while (*string >= '0' && *string <= '9')
    {
      padcount += *string++ - '0';
      padcount *= 10;
    }
  if (*string == '.')
    {
      string++;
      padcount += *string++ - '0';
    }
  if (*string == '*')
    {
      string++;
      padcount *= nlines;
    }
  while (*string)
    (*outfun) (*string++);

  /* padcount is now in units of tenths of msec.  */
  padcount *= speeds[ospeed];
  padcount += 500;
  padcount /= 1000;
  if (speeds[ospeed] < 0)
    padcount = -padcount;
  else
    {
      padcount += 50;
      padcount /= 100;
    }

  while (padcount-- > 0)
    (*outfun) (PC);
}


#ifdef VMS

#include <rmsdef.h>
#include <fab.h>
#include <nam.h>

static int
legal_filename_p (fn)
     char *fn;
{
  struct FAB fab = cc$rms_fab;
  struct NAM nam = cc$rms_nam;
  char esa[NAM$C_MAXRSS];

  fab.fab$l_fna = fn;
  fab.fab$b_fns = strlen(fn);
  fab.fab$l_nam = &nam;
  fab.fab$l_fop = FAB$M_NAM;

  nam.nam$l_esa = esa;
  nam.nam$b_ess = sizeof esa;

  return SYS$PARSE(&fab, 0, 0) == RMS$_NORMAL;
}

#endif /* VMS */

/* Find the termcap entry data for terminal type `name'
   and store it in the block that `bp' points to.
   Record its address for future use.

   If `bp' is zero, space is dynamically allocated.  */

#if defined(M_I86CM) || defined(M_I86LM)
long
#else
int
#endif
tgetent (bp, name)
     char *bp, *name;
{
  register char *tem;
  register int fd;
  struct buffer buf;
  register char *bp1;
  char *bp2;
  char *term;
  int malloc_size = 0;
  register int c;
  char *tcenv;			/* TERMCAP value, if it contais :tc=.  */
  char *indirect = 0;		/* Terminal type in :tc= in TERMCAP value.  */
  int filep;

  tem = (char *) getenv ("TERMCAP");
  if (tem && *tem == 0) tem = 0;

#ifdef VMS
  filep = tem && legal_filename_p (tem);
#else
#ifdef EMX
  filep = (tem != NULL && ((*tem == '/') || (*tem == '\\') ||
                      (isascii (*tem) && isalpha (*tem) && (tem[1] == ':'))));
#else
  filep = tem && (*tem == '/');
#endif
#endif /* VMS */

  /* If tem is non-null and starts with / (in the un*x case, that is),
     it is a file name to use instead of /etc/termcap.
     If it is non-null and does not start with /,
     it is the entry itself, but only if
     the name the caller requested matches the TERM variable.  */

#ifdef EMX
  term = getenv("TERM");

  if (tem != NULL && !filep &&
                           strcmp (name, (term != NULL ? term : "ansi")) == 0)
#else
  if (tem && !filep && !strcmp (name, getenv ("TERM")))
#endif
    {
      indirect = tgetst1 (find_capability (tem, "tc"), 0);
      if (!indirect)
	{
	  if (!bp)
	    bp = tem;
	  else
	    strcpy (bp, tem);
	  goto ret;
	}
      else
	{			/* we will need to read /etc/termcap */
	  tcenv = tem;
 	  tem = 0;
	}
    }
  else
    indirect = (char *) 0;

  if (!tem)
#ifdef VMS
    tem = "emacs_library:[etc]termcap.dat";
#else
#ifdef EMX
    {
      char tcfile[256];

      _searchenv ("termcap.dat", "INIT", tcfile);
      if (tcfile[0] == 0)
        _searchenv ("termcap.dat", "EMXETC", tcfile);
      if (tcfile[0] != 0)
        tem = strdup (tcfile);
      else
        tem = "/emx/etc/termcap.dat";
    }
#else
    tem = "/etc/termcap";
#endif
#endif

  /* Here we know we must search a file and tem has its name.  */

  fd = open (tem, 0, 0);
  if (fd < 0)
    return -1;

  buf.size = BUFSIZE;
  buf.beg = (char *) xmalloc (buf.size);
  term = indirect ? indirect : name;

  if (!bp)
    {
      malloc_size = indirect ? strlen (tcenv) + 1 : buf.size;
      bp = (char *) xmalloc (malloc_size);
    }
  bp1 = bp;

  if (indirect)			/* copy the data from the environment variable */
    {
      strcpy (bp, tcenv);
      bp1 += strlen (tcenv);
    }

  while (term)
    {
      /* Scan file, reading it via buf, till find start of main entry */
      if (scan_file (term, fd, &buf) == 0)
	return 0;

      /* Free old `term' if appropriate.  */
      if (term != name)
	free (term);

      /* If `bp' is malloc'd by us, make sure it is big enough.  */
      if (malloc_size)
	{
	  malloc_size = bp1 - bp + buf.size;
	  tem = (char *) xrealloc (bp, malloc_size);
	  bp1 += tem - bp;
	  bp = tem;
	}

      bp2 = bp1;

      /* Copy the line of the entry from buf into bp.  */
      tem = buf.ptr;
      while ((*bp1++ = (char) c = *tem++) && c != '\n')
	/* Drop out any \ newline sequence. */
	if (c == '\\' && *tem == '\n')
	  {
	    bp1--;
	    tem++;
	  }
      *bp1 = 0;

      /* Does this entry refer to another terminal type's entry?  */
      /* If something is found, copy it into heap and null-terminate it */
      term = tgetst1 (find_capability (bp2, "tc"), 0);
    }

  close (fd);
  free (buf.beg);

  if (malloc_size)
    {
      bp = (char *) xrealloc (bp, bp1 - bp + 1);
    }

 ret:
  term_entry = bp;
  if (malloc_size)
#if defined(M_I86CM) || defined(M_I86LM)
    return (long) bp;
#else
    return (int) bp;
#endif
  return 1;
}

/* Given file open on `fd' and buffer `bufp',
   scan the file from the beginning until a line is found
   that starts the entry for terminal type `string'.
   Returns 1 if successful, with that line in `bufp',
   or returns 0 if no entry found in the file.  */

static int
scan_file (string, fd, bufp)
     char *string;
     int fd;
     register struct buffer *bufp;
{
  register char *end;

  bufp->ptr = bufp->beg;
  bufp->full = 0;
  bufp->ateof = 0;
  *bufp->ptr = 0;

  lseek (fd, 0L, 0);

  while (!bufp->ateof)
    {
      /* Read a line into the buffer */
      end = 0;
      do
	{
	  /* if it is continued, append another line to it,
	     until a non-continued line ends */
	  end = gobble_line (fd, bufp, end);
	}
      while (!bufp->ateof && end[-2] == '\\');

      if (*bufp->ptr != '#'
	  && name_match (bufp->ptr, string))
	return 1;

      /* Discard the line just processed */
      bufp->ptr = end;
    }
  return 0;
}

/* Return nonzero if NAME is one of the names specified
   by termcap entry LINE.  */

static int
name_match (line, name)
     char *line, *name;
{
  register char *tem;

  if (!compare_contin (line, name))
    return 1;
  /* This line starts an entry.  Is it the right one?  */
  for (tem = line; *tem && *tem != '\n' && *tem != ':'; tem++)
    if (*tem == '|' && !compare_contin (tem + 1, name))
      return 1;

  return 0;
}

static int
compare_contin (str1, str2)
     register char *str1, *str2;
{
  register int c1, c2;
  while (1)
    {
      c1 = *str1++;
      c2 = *str2++;
      while (c1 == '\\' && *str1 == '\n')
	{
	  str1++;
	  while ((c1 = *str1++) == ' ' || c1 == '\t');
	}
      if (c2 == '\0')		/* end of type being looked up */
	{
	  if (c1 == '|' || c1 == ':') /* If end of name in data base, */
	    return 0;		/* we win. */
	  else
	    return 1;
        }
      else if (c1 != c2)
	return 1;
    }
}

/* Make sure that the buffer <- `bufp' contains a full line
   of the file open on `fd', starting at the place `bufp->ptr'
   points to.  Can read more of the file, discard stuff before
   `bufp->ptr', or make the buffer bigger.

   Returns the pointer to after the newline ending the line,
   or to the end of the file, if there is no newline to end it.

   Can also merge on continuation lines.  If `append_end' is
   nonzero, it points past the newline of a line that is
   continued; we add another line onto it and regard the whole
   thing as one line.  The caller decides when a line is continued.  */

static char *
gobble_line (fd, bufp, append_end)
     int fd;
     register struct buffer *bufp;
     char *append_end;
{
  register char *end;
  register int nread;
  register char *buf = bufp->beg;
  register char *tem;

  if (append_end == 0)
    append_end = bufp->ptr;

  while (1)
    {
      end = append_end;
      while (*end && *end != '\n') end++;
      if (*end)
        break;
      if (bufp->ateof)
	return buf + bufp->full;
      if (bufp->ptr == buf)
	{
	  if (bufp->full == bufp->size)
	    {
	      bufp->size *= 2;
	      tem = (char *) xrealloc (buf, bufp->size);
	      bufp->ptr += tem - buf;
	      append_end += tem - buf;
	      bufp->beg = buf = tem;
	    }
	}
      else
	{
	  append_end -= bufp->ptr - buf;
	  bcopy (bufp->ptr, buf, bufp->full -= bufp->ptr - buf);
	  bufp->ptr = buf;
	}
      if (!(nread = read (fd, buf + bufp->full, bufp->size - bufp->full - 1)))
	bufp->ateof = 1;
      bufp->full += nread;
      if (bufp->full != bufp->size)
	buf[bufp->full] = 0;
    }
  return end + 1;
}

#ifdef TEST

#include <stdio.h>

main (argc, argv)
     int argc;
     char **argv;
{
  char *term;
  char *buf;

  term = argv[1];
  printf ("TERM: %s\n", term);

  buf = (char *) tgetent (0, term);
  if ((int) buf <= 0)
    {
      printf ("No entry.\n");
      return 0;
    }

  printf ("Entry: %s\n", buf);

  tprint ("cm");
  tprint ("AL");

  printf ("co: %d\n", tgetnum ("co"));
  printf ("am: %d\n", tgetflag ("am"));
}

tprint (cap)
     char *cap;
{
  char *x = tgetstr (cap, 0);
  register char *y;

  printf ("%s: ", cap);
  if (x)
    {
      for (y = x; *y; y++)
	if (*y <= ' ' || *y == 0177)
	  printf ("\\%0o", *y);
	else
	  putchar (*y);
      free (x);
    }
  else
    printf ("none");
  putchar ('\n');
}

#endif /* TEST */
