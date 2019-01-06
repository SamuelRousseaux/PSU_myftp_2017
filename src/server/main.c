/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "server.h"

int check_args(int argc, char **argv)
{
	if (argc != 3) {
		printf("\n%s\n", HELP);
		return (FAILURE);
	}
	for (size_t i = 0 ; i < strlen(argv[1]) ; i++)
		if (argv[1][i] < '0' || argv[1][i] > '9') {
			fprintf(stderr, "%s", ERROR_NB_PORT);
			return (FAILURE);
		}
	if (chdir(argv[2]) == -1) {
		fprintf(stderr, "%s: %s\n", argv[2], strerror(errno));
		return (FAILURE);
	}
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	server_t serv;

	if (check_args(argc, argv) == FAILURE)
		return (ERROR);
	if (set_up_server(argv[1], &serv) == FAILURE)
		return (ERROR);
	if (loop(serv) == FAILURE)
		return (ERROR);
	return (0);
}
