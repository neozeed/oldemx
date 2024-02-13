/* version.c */

#include <stdio.h>
#include <stdlib.h>

int main (void);
static void bit (char *s, int n);


static void bit (char *s, int n)
    {
    (void)printf ("%s  %s\n", s, ((_emx_env & n) ? "YES" : "NO"));
    }


int main (void)
    {
    (void)printf ("emx version %s\n", _emx_vprt);
    bit ("VCPI     ", 0x001);
    bit ("XMS      ", 0x002);
    bit ("VDISK 3.3", 0x004);
    bit ("DESQview ", 0x008);
    bit ("287      ", 0x010);
    bit ("387      ", 0x020);
    bit ("OS/2 2.0 ", 0x200);
    bit ("-t       ", 0x400);
    (void)printf ("Available memory: %d KByte\n", _memavail () * 4);
    return (0);
    }
