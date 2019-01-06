/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "server.h"

static char *dico[] = {
	"USER", "PASS", "HELP", "QUIT", "NOOP", "CWD", "CDUP",
	"DELE",	"PWD", "PASV", "PORT", "RETR", "STOR", "LIST",
	"SYST", "FEAT", "TYPE"
};

static void (*function_ptr[])(char *, client_t *, server_t *) = {
	user,
	pass,
	help,
	quit,
	noop,
	cwd,
	cdup,
	dele,
	pwd,
	pasv,
	port,
	retr,
	stor,
	list,
	syst,
	feat,
	typei
};

void choose_func(char *command, client_t *client, server_t *s)
{
	int i = 0;
	char *tmp = strdup(command);

	tmp = strsep(&tmp, " ");
	for (i = 0 ; i < 17 ; i++)
		if (strncasecmp(dico[i], tmp, strlen(dico[i])) == 0) {
			function_ptr[i](command, client, s);
			break;
		}
	if (i == 17) {
		printf("%s: Unknown command\n", tmp);
		send_msg("500 Unknown command\n", s->csock);
	}
}

static int client_loop(server_t s)
{
	client_t *client = malloc(sizeof(client_t));
	char *buffer;

	client->user = FALSE;
	client->pass = FALSE;
	client->mode = 0;
	client->run = TRUE;
	printf("Client Connected\nAddress: %s\n", inet_ntoa(s.cin.sin_addr));
	send_msg("220 MyFtp Connected\r\n", s.csock);
	while (client->run == TRUE) {
		while ((buffer = gnl(s.csock)) == NULL);
		if (buffer[strlen(buffer) - 1] == '\r')
			buffer[strlen(buffer) - 1] = '\0';
		choose_func(buffer, client, &s);
		free(buffer);
	}
	printf("%s: Client disconnected\n", inet_ntoa(s.cin.sin_addr));
	close (s.csock);
	return (SUCCESS);
}

int loop(server_t s)
{
	unsigned int len = sizeof(s.sin);
	int pid;

	while (1) {
		s.csock = accept(s.ssock, (sockaddr *)&s.cin, &len);
		if (s.ssock == FAILURE)
			return (perror_ret("accept()"));
		pid = fork();
		if (pid == 0) {
			client_loop(s);
		} else if (pid > 0)
			close(s.csock);
		else {
			close(s.ssock);
			close(s.csock);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
