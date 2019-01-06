/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#ifndef SERVER_H_
# define SERVER_H_

# define HELP "USAGE:\t./server port path\n\n" \
	"\tport is the port number on which the server socket listens\n" \
	"\tpath is the path to the home directory for the Anonymous user\n"
# define ERROR_NB_PORT "Error: port must be a number\n"

# define HELP_SERV "214-The Following commands are recognized." \
	" USER PASS CWD  CDUP QUIT DELE PWD" \
	" PASV PORT HELP NOOP RETR STOR LIST\n"

# define SUCCESS	0
# define FAILURE	-1
# define ERROR		84

#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

enum BOOL
{
	TRUE,
	FALSE,
	UNDEFINED
};

typedef struct	s_server
{
	sockaddr_in	sin;
	sockaddr_in	cin;
	sockaddr_in	datasin;
	sockaddr_in	datacin;
	int		ssock;
	int		csock;
	int		datassock;
	int		datacsock;
}		server_t;

typedef struct	s_client
{
	enum BOOL	user;
	enum BOOL	pass;
	int		mode;
	enum BOOL	run;
}		client_t;

char *gnl(int);
int loop(server_t);
int perror_ret(char *);
int set_up_server(char *, server_t *);
int set_up_new_connection(int, server_t *);

void send_msg(char *, int);

char *ret_after_sep(char *, char);

void user(char *, client_t *, server_t *);
void pass(char *, client_t *, server_t *);
void help(char *, client_t *, server_t *);
void quit(char *, client_t *, server_t *);
void noop(char *, client_t *, server_t *);
void cwd(char *, client_t *, server_t *);
void cdup(char *, client_t *, server_t *);
void dele(char *, client_t *, server_t *);
void pwd(char *, client_t *, server_t *);
void pasv(char *, client_t *, server_t *);
void port(char *, client_t *, server_t *);
void retr(char *, client_t *, server_t *);
void stor(char *, client_t *, server_t *);
void list(char *, client_t *, server_t *);
void syst(char *, client_t *, server_t *);
void feat(char *, client_t *, server_t *);
void typei(char *, client_t *, server_t *);

#endif
