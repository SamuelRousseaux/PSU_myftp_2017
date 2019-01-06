/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

int set_up_server(char *port, server_t *serv)
{
	size_t size = sizeof(serv->sin);

	serv->ssock = socket(AF_INET, SOCK_STREAM, 0);
	if (serv->ssock == -1)
		return (perror_ret("socket()"));
	serv->sin.sin_addr.s_addr = htonl(INADDR_ANY);
	serv->sin.sin_family = AF_INET;
	serv->sin.sin_port = htons(atoi(port));
	if (bind(serv->ssock, (sockaddr *)&serv->sin, size) == FAILURE)
		return (perror_ret("bind()"));
	if (listen(serv->ssock, 1) == FAILURE)
		return (perror_ret("listen()"));
	return (SUCCESS);
}

int set_up_new_connection(int port, server_t *serv)
{
	size_t size = sizeof(serv->datasin);

	serv->datassock = socket(AF_INET, SOCK_STREAM, 0);
	if (serv->datassock == -1)
		return (perror_ret("socket()"));
	serv->datasin.sin_addr.s_addr = htonl(INADDR_ANY);
	serv->datasin.sin_family = AF_INET;
	serv->datasin.sin_port = htons(port);
	if (bind(serv->datassock, (sockaddr *)&serv->datasin, size) == FAILURE)
		return (perror_ret("bind()"));
	if (listen(serv->datassock, 1) == FAILURE)
		return (perror_ret("listen()"));
	return (SUCCESS);
}
