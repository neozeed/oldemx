/* hexdump.c */

/* test setmode() */

#include <stdlib.h>
#include <io.h>
#include <fcntl.h>

#define FALSE 0
#define TRUE  1

static int opt_b = FALSE;
static int opt_t = FALSE;
static unsigned char inp_buf[10240];
static char out_buf[100];
static char hex[] = "0123456789ABCDEF";

static void usage (void)
    {
    (void)puts ("Usage: hexdump [-b] [-t] [<input_file>]");
    exit (1);
    }

static void flush (void)
    {
    if (write (1, out_buf, strlen (out_buf)) != strlen (out_buf))
        {
        perror ("write() failed");
        exit (2);
        }
    }


int main (int argc, char *argv[])
    {
    int i, fd, c, x, m, n;
    char *d;

    for (i = 1; i < argc; ++i)
        if (strcmp (argv[i], "-b") == 0)
            opt_b = TRUE;
        else if (strcmp (argv[i], "-t") == 0)
            opt_t = TRUE;
        else if (argv[i][0] == '-')
            usage ();
        else
            break;
    m = 0;
    if (opt_b) m |= O_BINARY;
    if (opt_t) m |= O_TEXT;
    if (i == argc)
        {
        fd = 0;         /* stdin */
        if (m != 0 && setmode (fd, m) < 0)
            {
            perror ("setmode() failed");
            return (2);
            }
        }
    else if (i + 1 == argc)
        {
        fd = open (argv[i], O_RDONLY | m);
        if (fd < 0)
            {
            perror ("open() failed");
            return (1);
            }
        }
    else
        usage ();
    x = 0; d = out_buf; n = 0; i = 0;
    for (;;)
        {
        if (i >= n)
            {
            i = 0;
            n = read (fd, inp_buf, sizeof (inp_buf));
            if (n < 0)
                {
                perror ("read() failed");
                return (2);
                }
            if (n == 0)
                break;
            }
        if (x >= 16)
            {
            *d++ = '\n'; *d = 0;
            flush ();
            x = 0; d = out_buf;
            }
        c = inp_buf[i++];
        if (x != 0)
            *d++ = ' ';
        ++x;
        *d++ = hex[(c >> 4) & 0x0f];
        *d++ = hex[c & 0x0f];
        }
    if (out_buf[0] != 0)
        {
        *d++ = '\n'; *d = 0;
        flush ();
        }
    return (0);
    }
