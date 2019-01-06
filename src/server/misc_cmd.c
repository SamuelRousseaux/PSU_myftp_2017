/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include "server.h"

void help(char *command, client_t *client, server_t *s)
{
	if (client->pass == FALSE)
		send_msg("530 Please login with USER and PASS.\n", s->csock);
	else
		send_msg(HELP_SERV, s->csock);
	(void)command;
	(void)client;
}

void quit(char *command, client_t *client, server_t *s)
{
	client->run = FALSE;
	send_msg("221 Bye! Have a nice day!\n", s->csock);
	(void)command;
}

void noop(char *command, client_t *client, server_t *s)
{
	if (client->pass == FALSE)
		send_msg("530 Please login with USER and PASS.\n", s->csock);
	else
		send_msg("200 NOOP ok.\n", s->csock);
	(void)command;
	(void)client;
}
