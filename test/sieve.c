/* sieve.c (emx/gcc) */

/* Define BITS to use bit encoding instead of byte encoding */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define FALSE   0
#define TRUE    1

#define N(x) ((x)/3)

typedef unsigned long ULONG;
typedef unsigned char BYTE;

#if defined (BITS)

#define index(c) (((c)>>3)+sizeof(ULONG))
#define mask(c)  (1<<((c)&0x07))
#define BIT_ON(map,c) (map[index(c)] & mask(c))
#define BIT_OFF(map,c) (!BIT_ON(map,c))
#define SET_TRUE(map,c) map[index(c)] |= mask(c)
#define SET_FALSE(map,c) map[index(c)] &= ~mask(c)
#define BYTES(s) (((s)+7)>>3)

#else

#define BIT_ON(map,c) map[c]
#define BIT_OFF(map,c) !map[c]
#define SET_TRUE(map,c) map[c] = 1
#define SET_FALSE(map,c) map[c] = 0
#define BYTES(s) (s)

#endif

static ULONG isqrt (ULONG x);
static void usage (void);


static ULONG isqrt (ULONG x)
    {
    ULONG l, r, m;

    l = 1; r = x;
    while (l < r)
        {
        m = (l+r) / 2;
        if (m > 46340) m = 46340;  /* avoid overflow when computing m*m */
        if (m*m < x)
            l = m+1;
        else if (m*m > x)
            r = m-1;
        else
            return (m);
        }
    return ((l+r)/2);
    }


static void usage (void)
    {
    (void)fputs ("Usage: sieve [-p] <number>\n", stderr);
    exit (1);
    }


int main (int argc, char *argv[])
    {
    ULONG sqrt_size, i, j, n, primes, size;
    int incr, jincr, idx, print_flag;
    long arg;
    char *p;
    BYTE *bitmap;

    print_flag = FALSE;
    for (idx = 1; idx < argc; ++idx)
        if (strcmp (argv[idx], "-p") == 0)
            print_flag = TRUE;
        else
            break;
    if (argc - idx != 1)
        usage ();
    errno = 0;
    arg = strtol (argv[idx], &p, 10);     /* strtoul() not implemented */
    if (errno != 0 || *p != 0 || arg < 10 || arg > 2000000000)
        usage ();
    size = (ULONG)arg;
    bitmap = malloc (BYTES (N (size)+1));
    if (bitmap == NULL)
        {
        (void)fputs ("Out of memory\n", stderr);
        exit (2);
        }
    (void)memset (bitmap, 0, sizeof (bitmap));
    sqrt_size = isqrt (size);
    for (i = 5, incr = 4, n = 1; i <= sqrt_size; i += (incr=6-incr), ++n)
        if (BIT_OFF (bitmap, n))
            for (j = i, jincr = incr; j <= size/i; j += (jincr = 6-jincr))
                SET_TRUE (bitmap, N(i*j));
    if (print_flag)
        (void)printf ("2 3 ");
    for (i = 5, incr = 4, n = 1, primes = 2; i <= size; i += (incr=6-incr), ++n)
        if (BIT_OFF (bitmap, n))
            {
            ++primes;
            if (print_flag)
                (void)printf ("%lu ", i);
            }
    (void)printf ("\n%lu primes\n", primes);
    return (0);
    }
