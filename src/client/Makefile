##
## EPITECH PROJECT, 2023
## B-NWP-400-PAR-4-1-myftp-laetitia.bousch
## File description:
## Makefile
##

SRC			=	src/main.c						\
				src/handle_client.c				\
				src/handle_client_bis.c			\
				src/command/base_user_cmd.c		\
				src/command/funct_create_bis.c	\
				src/command/funct_create_eight.c\
				src/command/funct_create_six.c	\
				src/command/funct_create_seven.c\
				src/command/funct_create_ten.c	\
				src/command/funct_create_five.c	\
				src/command/funct_create_tree.c	\
				src/command/funct_create.c		\
				src/command/funct_response_create.c	\
				src/command/funct_use.c			\
				src/command/funct_list.c			\
				src/command/help.c				\
				src/command/user_cmd.c			\
				src/command/subscribe_cmd.c	\
				src/command/user_cmd_bis.c		\
				src/my_str_to_word_array.c		\
				src/my_str_to_word_array_command.c		\
				src/my_str_to_word_array_command_bis.c		\
				src/clear_all.c					\
				src/utils_function.c			\
				src/utils_function_bis.c		\
				src/to_create_response.c		\
				src/to_read_command_input.c		\
				src/to_read_command_server.c	\
				src/command/msg_cmd.c			\
				src/command/funct_response.c	\
				src/command/funct_response_bis.c\
				src/command/funct_response_tree.c\

OBJ			=	$(SRC:.c=.o)

NAME		=	../../myteams_cli

CFLAGS		=	-Wall -Wextra -I ../../libs/myteams

CPPFLAGS	=	-iquote ./include

LDFLAGS		+=	-L ../../libs/myteams -lmyteams -luuid

CC			=	gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

debug: CFLAGS += -g3
debug: re

clean:
	$(RM) $(NAME) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

./PHONY: all clean fclean
