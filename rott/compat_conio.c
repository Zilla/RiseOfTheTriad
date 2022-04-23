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

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

unsigned int outp(int port, int value)
{
    int fd = open("/dev/port", O_WRONLY);
    lseek(fd, port, SEEK_SET);
    write(fd, &value, 1);
    close(fd);
    return (unsigned int)value;
}

unsigned int outpw(int port, int value)
{
    int fd = open("/dev/port", O_WRONLY);
    lseek(fd, port, SEEK_SET);
    write(fd, &value, 2);
    close(fd);
    return (unsigned int)value;
}

unsigned int inp(int port)
{
    unsigned int ret;
    int fd = open("/dev/port", O_RDONLY);
    lseek(fd, port, SEEK_SET);
    read(fd, &ret, 1);
    close(fd);
    return (unsigned int)ret;
}

int getch(void)
{
    return getchar();
}