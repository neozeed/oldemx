/* GNU termcap */

/* Work-alike for termcap, plus extra features.
   Copyright (C) 1985, 1986 Free Software Foundation, Inc. */

/* see termcap.c for WARRANTY and LICENSE */

extern short ospeed;
extern char PC;

#if defined(M_I86CM) || defined(M_I86LM)
long tgetent (char *bp, char *name);
#else
int tgetent (char *bp, char *name);
#endif

int tgetnum (char *cap);
int tgetflag (char *cap);
char *tgetstr (char *cap, char **area);

void tputs (char *string, int nlines, int (*outfun)(int));
