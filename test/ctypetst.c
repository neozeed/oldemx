/* ctypetst.c */

#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define TEST(is) do {start (#is); \
                     for (i=-1; i<=255; ++i) if (is(i)) show(i); \
                     end (); } while (0)

static int pos, indent, str;

static void start (char *s)
    {
    (void)fputs (s, stdout);
    (void)fputs (": ", stdout);
    pos = indent = strlen (s) + 2;
    str = 0;
    }

static void end (void)
    {
    if (str != 0)
        {
        str = 0; (void)putchar ('"');
        }
    if (pos != 0)
        {
        (void)putchar ('\n'); pos = 0;
        }
    }

static void show (int i)
    {
    static char hex[] = "0123456789ABCDEF";

    if (pos > 70)
        {
        int j;

        if (str)
            {
            str = 0; (void)putchar ('"');
            }
        (void)putchar ('\n');
        for (j = 0; j < indent; ++j)
            (void)putchar (' ');
        pos = indent;
        }
    if (i >= ' ' && i < 127)
        {
        if (!str)
            {
            if (pos != indent)
                {
                (void)putchar (' '); ++pos;
                }
            str = 1; (void)putchar ('"'); ++pos;
            }
        if (i == '"' || i == '\\')
            {
            (void)putchar ('\\'); ++pos;
            }
        (void)putchar (i); ++pos;
        }
    else
        {
        if (str)
            {
            str = 0;
            (void)putchar ('"'); ++pos;
            }
        if (pos != indent)
            {
            (void)putchar (' '); ++pos;
            }
        if (i < 0)
            {
            (void)putchar ('-'); ++pos;
            i = -i;
            }
        (void)putchar (hex[(i/16)%16]);
        (void)putchar (hex[i%16]);
        pos += 2;
        }
    }

int main (int argc, char *argv[])
    {
    int i, buf_mode;

    buf_mode = _IONBF;
    for (i = 1; i < argc; ++i)
        if (strcmp (argv[i], "-l") == 0)
            buf_mode = _IOLBF;
        else if (strcmp (argv[i], "-f") == 0)
            buf_mode = _IOFBF;
        else if (strcmp (argv[i], "-n") == 0)
            buf_mode = _IONBF;
        else
            {
            (void)puts ("Usage: ctypetst [-f] [-l] [-n]");
            return (1);
            }
    (void)setvbuf (stdout, NULL, buf_mode, BUFSIZ);
    TEST (isprint);
    TEST (isgraph);
    TEST (isupper);
    TEST (islower);
    TEST (isalpha);
    TEST (isdigit);
    TEST (isxdigit);
    TEST (isalnum);
    TEST (ispunct);
    TEST (isspace);
    TEST (iscntrl);
    return (0);
    }
