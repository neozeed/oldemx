/* _searche.c (emx/gcc) -- Copyright (c) 1990-1992 by Eberhard Mattes */

#include <stdlib.h>
#include <string.h>
#include <io.h>

void _searchenv (const char *file, const char *var, char *path)
    {
    char *list, *end;
    int i;

    strcpy (path, file);
    if (access (path, 4) == 0)
        return;
    list = getenv (var);
    if (list != NULL)
        for (;;)
            {
            while (*list == ' ' || *list == '\t') ++list;
            if (*list == 0) break;
            end = list;
            while (*end != 0 && *end != ';') ++end;
            i = end - list;
            while (i>0 && (list[i-1] == ' ' || list[i-1] == '\t')) --i;
            if (i != 0)
                {
                memcpy (path, list, i);
                if (list[i-1] != '/' && list[i-1] != '\\' && list[i-1] != ':')
                    path[i++] = '\\';
                strcpy (path+i, file);
                if (access (path, 4) == 0)
                    return;
                }
            if (*end == 0) break;
            list = end + 1;
            }
    path[0] = 0;
    }
