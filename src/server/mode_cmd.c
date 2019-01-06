/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

static int port_error(char *port, server_t *s)
{
	int n = 0;

	for (int i = 0 ; port[i] != '\0' ; i++)
		if ((port[i] < '0' || port[i] > '9') && port[i] != ','
		&& port[i] != '\r' && port[i] != '\n') {
			send_msg("500 Incorrect format.\n", s->csock);
			return (0);
		} else if (port[i] == ',')
			n++;
	if (n != 5) {
		send_msg("500 Incorrect format.\n", s->csock);
		return (0);
	}
	return (1);
}

static int get_port(char *line, server_t *s)
{
	int port = 0;
	int n = 0;

	if (!port_error(line, s))
		return (0);
	for (int i = 0 ; line[i] != '\0' ; i++)
		if (line[i] == ',')
			n++;
		else {
			if (n == 4 && port == 0)
				port += (atoi(line + i) * 256);
			else if (n == 5) {
				port += atoi(line + i);
				return (port);
			}
		}
	return (-1);
}

static char *ret_pasv_line(server_t *s)
{
	char *line = malloc(sizeof(char) * 24);
	char tmp[4] = { 0 };
	int port = htons(s->datasin.sin_port);

	if (line == NULL)
		return (NULL);
	strcat(line, "(");
	strcat(line, inet_ntoa(s->cin.sin_addr));
	for (int i = 0 ; line[i] != '\0' ; i++)
		if (line[i] == '.')
			line[i] = ',';
	strcat(line, ",");
	sprintf(tmp, "%d", (int)(port / 256));
	strcat(line, tmp);
	strcat(line, ",");
	sprintf(tmp, "%d", port % 256);
	strcat(line, tmp);
	strcat(line, ").\n");
	return (line);
}

void pasv(char *command, client_t *client, server_t *s)
{
	int range = (65636 - 1024);

	if (client->pass == FALSE)
		send_msg("530 Please login with USER and PASS.\n", s->csock);
	else {
		client->mode = 2;
		while (set_up_new_connection(rand() % range, s) == FAILURE);
		send_msg("227 Entering passive mode ", s->csock);
		send_msg(ret_pasv_line(s), s->csock);
	}
	(void)command;
}

void port(char *command, client_t *client, server_t *s)
{
	int port = 0;

	if (client->pass == FALSE)
		send_msg("530 Please login with USER and PASS.\n", s->csock);
	else {
		port = get_port(ret_after_sep(command, ' '), s);
		if (port != -1) {
			client->mode = 1;
			if (set_up_new_connection(port, s) == FAILURE) {
				send_msg("500 Failed.\n", s->csock);
				return;
			}
			send_msg("200 Entering active mode.\n", s->csock);
		}
	}
}
