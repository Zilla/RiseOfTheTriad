/*
Copyright (C) 2022

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "compat_stdlib.h"

char *itoa(int val, char *str, int base)
{
   (void)base;
   sprintf(str, "%d", val);
   return str;
}

char *ltoa(long val, char *str, int base)
{
   (void)base;
   sprintf(str, "%ld", val);
   return str;
}

char *ultoa(unsigned long val, char *str, int base)
{
   (void)base;
   sprintf(str, "%lu", val);
   return str;
}

char *strupr(char *s)
{
    if(s == NULL)
        return NULL;

    int len = strlen(s);
    for(int i = 0; i < len; i++)
        s[i] = toupper(s[i]);

    return s;
}

long int filelength(int fd)
{
    struct stat st;

    if(fstat(fd, &st) != 0)
        return -1L;

    return (long int)st.st_size;
}