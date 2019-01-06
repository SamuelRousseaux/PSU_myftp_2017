/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include "server.h"

void syst(char *command, client_t *client, server_t *s)
{
	send_msg("215 UNIX Type: L8.\n", s->csock);
	(void)command;
	(void)client;
}

void feat(char *command, client_t *client, server_t *s)
{
	send_msg("200 Command Ok.\n", s->csock);
	(void)command;
	(void)client;
}

void typei(char *command, client_t *client, server_t *s)
{
	send_msg("200 Command OK.\n", s->csock);
	(void)command;
	(void)client;
}
