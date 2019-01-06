/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include "server.h"

void open_close_data_chan(int mode, server_t *s, client_t *c)
{
	unsigned int len = sizeof(s->datasin);

	if (mode == 1) {
		send_msg("150 Openning data connection.\n", s->csock);
		s->datacsock = accept(s->datassock, (sockaddr *)&s->datacin,
			     &len);
	}
	else if (mode == 2) {
		close(s->datacsock);
		c->mode = 0;
	}
}

void retr(char *command, client_t *client, server_t *s)
{
	char *buffer;
	int fd;

	if (client->pass == FALSE)
		send_msg("530 Please login with USER and PASS.\n", s->csock);
	else if (client->mode == 0)
		send_msg("425 Use PORT or PASV first.\n", s->csock);
	else {
		open_close_data_chan(1, s, client);
		fd = open(ret_after_sep(command, ' '), O_RDONLY);
		while ((buffer = gnl(fd)) != NULL) {
			send_msg(buffer, s->datacsock);
			send_msg("\n", s->datacsock);
		}
		send_msg("226 Transfer complete.\n", s->csock);
		open_close_data_chan(2, s, client);
		client->mode = 0;
	}
}

void stor(char *command, client_t *client, server_t *s)
{
	if (client->pass == FALSE)
		send_msg("530 Please login with USER and PASS.\n", s->csock);
	else if (client->mode == 0)
		send_msg("425 Use PORT or PASV first.\n", s->csock);
	else {
		client->mode = 0;
	}
	(void)command;
}

void list(char *command, client_t *client, server_t *s)
{
	FILE *fp;
	char buff[256];
	char cmd[256] = {0};

	if (client->pass == FALSE)
		send_msg("530 Please login with USER and PASS.\n", s->csock);
	else if (client->mode == 0)
		send_msg("425 Use PORT or PASV first.\n", s->csock);
	else {
		open_close_data_chan(1, s, client);
		strcat(cmd, "ls -l ");
		fp = popen(strcat(cmd, ret_after_sep(command, ' ')), "r");
		fgets(buff, 256, fp);
		if (buff[0] != 't')
			send_msg(buff, s->datacsock);
		while (fgets(buff, 256, fp) != NULL)
			send_msg(buff, s->datacsock);
		open_close_data_chan(2, s, client);
		send_msg("226 Closing data connection.\n", s->csock);
	}
}

void dele(char *command, client_t *client, server_t *s)
{
	char tmp[256] = { 0 };
	int ret;

	if (client->pass == FALSE)
		send_msg("530 Please login with USER and PASS.\n", s->csock);
	else {
		strcat(tmp, "rm ");
		strcat(tmp, ret_after_sep(command, ' '));
		ret = system(tmp);
		if (ret == -1 || (WIFEXITED(ret) && WEXITSTATUS(ret) != 0))
			send_msg("550 Cannot delete file.\n", s->csock);
		else
			send_msg("250 File successfully deleted.\n", s->csock);
	}
	(void)client;
}
