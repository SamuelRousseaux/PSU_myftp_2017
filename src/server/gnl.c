/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *gnl(int fd)
{
	int i = 0;
	char *str = malloc(sizeof(char) * 2);
	char buffer[1];

	if (str == NULL)
		return (NULL);
	while (read(fd, buffer, 1) > 0) {
		if (buffer[0] == '\n' || buffer[0] == '\0') {
			str[i] = '\0';
			return (str);
		}
		str[i] = buffer[0];
		str[i + 1] = '\0';
		i++;
		str = realloc(str, sizeof(char) * (i + 2));
		if (str == NULL)
			return (NULL);
	}
	return (NULL);
}
