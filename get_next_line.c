/*
** EPITECH PROJECT, 2018
** get_next_line
** File description:
** try not to segfault, good luck :)
*/

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int     back_slashn(char *buff, int size)
{
    int i = 0;

    while (buff[i] != '\0' && i < size) {
        if (buff[i] == '\n')
            return (i);
        i++;
    }
    return (-1);
}

char    *concat(char *buff, char *line, int size)
{
    int     i = 0;
    int     j = 0;
    char    *tmp;

    while (line && line[i++]);
    size += i;
    tmp = malloc(size);
    i = 0;
    while (line && line[i]) {
        tmp[i] = line[i];
        i++;
    }
    if (line != NULL)
        free(line);
    while (buff[j] != '\0' && buff[j] != '\n') {
        tmp[i + j] = buff[j];
        j++;
    }
    if (buff[0] == '\n')
        tmp[i + j++] = '\n';
    tmp[i + j] = '\0';
    return (tmp);
}

void    sup_to_n(char *buff)
{
    int i = 0;
    int j = 0;

    while (buff[i] && buff[i++] != '\n');
    while (buff[i]) {
        buff[j] = buff[i];
        i++;
        j++;
    }
    while (buff[j])
        buff[j++] = '\0';
}

char    *to_next_n(char *buff, char *line, int *size)
{
    int i = 0;

    while (buff[i] && buff[i++] != '\n');
    if (i - 1 >= 0 && buff[i - 1] == '\n')
        *size = -1;
    line = malloc(i);
    i = 0;
    while (buff[i] && buff[i] != '\n') {
        line[i] = buff[i];
        i++;
    }
    if (i == 0 && buff[0] == '\n')
        line[i++] = '\0';
    line[i] = '\0';
    return (line);
}

char    *get_next_line(int fd)
{
    static char buff[READ_SIZE];
    char        *line = NULL;
    int         size = 0;

    if (fd == -1)
        return (0);
    line = to_next_n(buff, line, &size);
    while (size >= 0 && back_slashn(buff, size) == -1) {
        size = read(fd, buff, READ_SIZE);
        line = concat(buff, line, size);
        size = (size == 0) ? -1 : size;
    }
    sup_to_n(buff);
    //printf("[%s]   [%s]\n", line, buff);
    if (line && line[0] == '\0' && buff[0] == '\0')
        return (NULL);
    return (line);
}
