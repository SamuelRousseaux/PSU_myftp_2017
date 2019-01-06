/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "server.h"

void cwd(char *command, client_t *client, server_t *s)
{
	if (client->pass == FALSE)
		send_msg("530 Please login with USER and PASS.\n", s->csock);
	else {
		if (chdir(ret_after_sep(command, ' ')) == -1)
			send_msg("550 Failed to change directory.\n",
				s->csock);
		else
			send_msg("250 Directory successfully changed.\n",
				s->csock);
	}
	(void)client;
}

void cdup(char *command, client_t *client, server_t *s)
{
	if (client->pass == FALSE)
		send_msg("530 Please login with USER and PASS.\n", s->csock);
	else {
		send_msg("250 Directory successfully changed.\n", s->csock);
		chdir("..");
	}
	(void)command;
	(void)client;
}

void pwd(char *command, client_t *client, server_t *s)
{
	FILE *fp;
	char path[256];

	if (client->pass == FALSE)
		send_msg("530 Please login with USER and PASS.\n", s->csock);
	else {
		fp = popen("pwd", "r");
		while (fgets(path, 256, fp) != NULL);
		pclose(fp);
		send_msg("257 \"", s->csock);
		path[strlen(path) - 1] = '\0';
		send_msg(path, s->csock);
		send_msg("\"\n", s->csock);
	}
	(void)command;
}
