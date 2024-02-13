/* stream.c */

#include <sys/emx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

void volatile done (void);
void finfo (FILE *f);

void volatile done (void)
    {
    char buf[100];

    fputs ("errno=", stderr);
    fputs (itoa (errno, buf, 10), stderr);
    fputc ('\n', stderr);
    fputs (strerror (errno), stderr);
    fputc ('\n', stderr);
    exit (1);
    }

void finfo (FILE *f)
    {
    prts ("buffer   = "); prti ((int)f->buffer); prtc ('\n');
    prts ("ptr      = "); prti ((int)f->ptr); prtc ('\n');
    prts ("rcount   = "); prti (f->rcount); prtc ('\n');
    prts ("wcount   = "); prti (f->wcount); prtc ('\n');
    prts ("handle   = "); prti (f->handle); prtc ('\n');
    prts ("buf_size = "); prti (f->buf_size); prtc ('\n');
    if (f->flags & _IOREAD) prts ("_IOREAD ");
    if (f->flags & _IOWRT) prts ("_IOWRT ");
    if (f->flags & _IORW) prts ("_IORW ");
    if (f->flags & _IOEOF) prts ("_IOEOF ");
    if (f->flags & _IOERR) prts ("_IOERR ");
    if (f->flags & O_APPEND) prts ("O_APPEND ");
    prts ((f->flags & O_BINARY) ? "O_BINARY " : "O_TEXT ");
    if (f->flags & F_DEV) prts ("F_DEV ");
    if (f->flags & F_INUSE) prts ("F_INUSE ");
    if (f->flags & F_STRING) prts ("F_STRING ");
    if (f->flags & F_REREAD) prts ("F_REREAD ");
    switch (f->flags & F_BUF_MASK)
        {
        case F_NO_BUF:   prts ("F_NO_BUF "); break;
        case F_USER_BUF: prts ("F_USER_BUF "); break;
        case F_CHAR_BUF: prts ("F_CHAR_BUF "); break;
        case F_LIB_BUF:  prts ("F_LIB_BUF "); break;
        case F_TMP_BUF:  prts ("F_TMP_BUF "); break;
        default:         prts ("[unknown buffer mode] "); break;
        }
    prtc ('\n');
    }

int main (int argc, char *argv[])
    {
    FILE *inp, *out;
    int c, i;
    char flag, buf_inp_flag, buf_out_flag, print_flag;

    buf_inp_flag = buf_out_flag = print_flag = 0;
    for (i = 1; i < argc; ++i)
        {
        if (strcmp (argv[i], "-bi") == 0)
            buf_inp_flag = 1;
        else if (strcmp (argv[i], "-bo") == 0)
            buf_out_flag = 1;
        else if (strcmp (argv[i], "-p") == 0)
            print_flag = 1;
        else
            break;
        }
    if (argc - i != 2)
        {
        fputs ("Usage: stream [-bi] [-bo] [-p] <input_file> <output_file>\n", stderr);
        return (1);
        }
    if (strcmp (argv[i], "-") == 0)
        {
        inp = stdin;
        }
    else
        {
        inp = fopen (argv[i], "rt");
        if (inp == NULL)
            {
            fputs ("Could not open ", stderr);
            fputs (argv[i], stderr);
            fputs (" for reading\n", stderr);
            done ();
            }
        }
    if (buf_inp_flag)
        setbuf (inp, malloc (BUFSIZ));
    ++i;
    if (strcmp (argv[i], "-") == 0)
        out = stdout;
    else
        {
        out = fopen (argv[i], "wt");
        if (out == NULL)
            {
            fputs ("Could not open ", stderr);
            fputs (argv[i], stderr);
            fputs (" for writing\n", stderr);
            done ();
            }
        }
    if (buf_out_flag)
        setbuf (out, malloc (BUFSIZ));
    if (print_flag)
        {
        prts ("inp:\n"); finfo (inp);
        prts ("out:\n"); finfo (out);
        flag = 0;
        }
    else
        flag = 1;
    for (;;)
        {
        c = getc (inp);
        if (c == EOF)
            break;
        putc (c, out);
        if (!flag)
            {
            flag = 1;
            prts ("inp:\n"); finfo (inp);
            prts ("out:\n"); finfo (out);
            }
        }
    if (inp != stdin && fclose (inp) != 0)
        {
        fputs ("fclose (inp) failed\n", stderr);
        done ();
        }
    if (out != stdout && fclose (out) != 0)
        {
        fputs ("fclose (out) failed\n", stderr);
        done ();
        }
    return (0);
    }
