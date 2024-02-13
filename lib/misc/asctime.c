/* asctime.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <time.h>
#include <string.h>

static char months[]="JanFebMarAprMayJunJulAugSepOctNovDec";
static char wdays[]="SunMonTueWedThuFriSat";

#define digit(i) (char)(((i)%10)+'0')

char *asctime (const struct tm *t)
    {
    static char result[26];

    (void)memcpy (result+0, wdays+t->tm_wday*3, 3);
    result[3] = ' ';
    (void)memcpy (result+4, months+t->tm_mon*3, 3);
    result[7] = ' ';
    result[8] = digit (t->tm_mday / 10);
    result[9] = digit (t->tm_mday / 1);
    result[10] = ' ';
    result[11] = digit (t->tm_hour / 10);
    result[12] = digit (t->tm_hour / 1);
    result[13] = ':';
    result[14] = digit (t->tm_min / 10);
    result[15] = digit (t->tm_min / 1);
    result[16] = ':';
    result[17] = digit (t->tm_sec / 10);
    result[18] = digit (t->tm_sec / 1);
    result[19] = ' ';
    result[20] = digit ((t->tm_year+1900) / 1000);
    result[21] = digit ((t->tm_year+1900) / 100);
    result[22] = digit ((t->tm_year+1900) / 10);
    result[23] = digit ((t->tm_year+1900) / 1);
    result[24] = '\n';
    result[25] = '\0';
    return (result);
    }
