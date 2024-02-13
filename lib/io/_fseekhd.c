/* _fseekhd.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdio.h>
#include <memory.h>

int _fseek_hdr (FILE *stream)
    {
    struct
        {
        char magic[2];
        char fill1[6];
        unsigned short hdr_size;
        } exe_hdr;
    struct
        {
        char sig[16];
        char bound;
        char fill1;
        unsigned short hdr_loc_lo;      /* cannot use long, alignment! */
        unsigned short hdr_loc_hi;
        } patch;
    int i;

    (void)fseek (stream, 0, SEEK_SET);
    if (fread (&exe_hdr, sizeof (exe_hdr), 1, stream) != 1)
        goto failure;
    if (memcmp (exe_hdr.magic, "MZ", 2) != 0)
        return (fseek (stream, 0, SEEK_SET) == -1 ? -1 : 0);
    if (fseek (stream, 16 * exe_hdr.hdr_size, SEEK_SET) == -1)
        goto failure;
    if (fread (&patch, sizeof (patch), 1, stream) != 1)
        goto failure;
    if (memcmp (patch.sig, "emx", 3) != 0)
        goto failure;
    if (fseek (stream, patch.hdr_loc_lo + 65536 * patch.hdr_loc_hi, SEEK_SET) == -1)
        goto failure;
    return (0);

failure:
    (void)fseek (stream, 0, SEEK_SET);
    return (-1);
    }
