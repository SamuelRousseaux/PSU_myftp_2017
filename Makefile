##
## EPITECH PROJECT, 2018
## *
## File description:
## *
##

NAME_SRV=	server

CC	=	gcc

CFLAGS	=	-W -Wall -Wextra -I./inc

SRC_SRV	=	src/server/auth_cmd.c		\
		src/server/dir_cmd.c		\
		src/server/error.c		\
		src/server/file_cmd.c		\
		src/server/fz_cmd.c		\
		src/server/gnl.c		\
		src/server/loop.c		\
		src/server/main.c		\
		src/server/misc_cmd.c		\
		src/server/mode_cmd.c		\
		src/server/send_msg.c		\
		src/server/set_up.c		\
		src/server/string_funcs.c

OBJ_SRV	=	$(SRC_SRV:.c=.o)

all:	$(NAME_SRV)

$(NAME_SRV):	$(OBJ_SRV)
	$(CC) -o $(NAME_SRV) $(OBJ_SRV)

clean:
	$(RM) $(OBJ_SRV)

fclean:	clean
	$(RM) $(NAME_SRV)

re:	fclean all

.PHONY:	all clean fclean re
