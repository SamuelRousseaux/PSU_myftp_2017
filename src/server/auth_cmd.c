/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include "server.h"

void user(char *command, client_t *client, server_t *s)
{
	if (client->user == FALSE || client->user == UNDEFINED) {
		if (strncasecmp(command, "USER Anonymous", 14) == 0)
			client->user = TRUE;
		else
			client->user = UNDEFINED;
		send_msg("331 Please specify the password.\r\n", s->csock);
	} else if (client->user == TRUE)
		send_msg("530 Can't change from guest user\r\n", s->csock);
	else
		send_msg("501 No such user\r\n", s->csock);
}

void pass(char *command, client_t *client, server_t *s)
{
	if (client->pass == FALSE) {
		if (client->user == TRUE) {
			client->pass = TRUE;
			send_msg("230 Login successful.\r\n", s->csock);
		} else if (client->user == UNDEFINED) {
			client->user = FALSE;
			send_msg("530 Login incorrect.\r\n", s->csock);
		} else
			send_msg("503 Login with USER first.\r\n", s->csock);
	}
	else if (client->pass == TRUE)
		send_msg("230 Already logged in.\r\n", s->csock);
	(void)command;
}
