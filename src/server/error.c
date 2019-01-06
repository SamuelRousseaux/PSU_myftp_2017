/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <stdio.h>
#include <errno.h>
#include "server.h"

int perror_ret(char *func)
{
	perror(func);
	return (FAILURE);
}
