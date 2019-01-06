/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

void send_msg(char *msg, int stream)
{
	write(stream, msg, strlen(msg));
}
