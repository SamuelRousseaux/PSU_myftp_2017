/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <string.h>
#include "server.h"

char *ret_after_sep(char *str, char sep)
{
	char *tmp = strdup(str);

	while (*tmp != '\0' && *tmp != sep)
		tmp++;
	if (*tmp == ' ')
		tmp++;
	return (tmp);
}
