##
## EPITECH PROJECT, 2023
## B-NWP-400-PAR-4-1-myftp-laetitia.bousch
## File description:
## Makefile
##

SRC			=	src/main.c									\
				src/client.c								\
				src/free_server.c							\
				src/handle_client.c							\
				src/init_server.c							\
				src/my_str_to_word_array.c					\
				src/read_new_command.c						\
				src/to_action_on_fd.c						\
				src/to_check_command.c						\
				src/to_clear_command.c						\
				src/to_connect_sock_buffer.c				\
				src/utils_funct.c							\
				src/lib/init_struct_sock_t.c				\
				src/lib/read_and_write_buffer.c				\
				src/lib/clear_buffer_of_n_octets.c			\
				src/command/funct_command_logout_login.c	\
				src/command/funct_command_create.c			\
				src/command/funct_command_create_bis.c		\
				src/command/funct_command_create_bis_bis.c	\
				src/command/funct_command_create_tree.c		\
				src/command/funct_command_create_eight.c	\
				src/command/funct_command_create_tree_bis.c	\
				src/command/funct_command_create_five.c		\
				src/command/funct_command_create_six.c		\
				src/command/funct_command_create_seven.c	\
				src/command/funct_command_user.c			\
				src/command/funct_command_list.c			\
				src/command/funct_command_list_bis.c		\
				src/command/funct_command_list_tree.c		\
				src/command/funct_command_users.c			\
				src/command/funct_command_send.c			\
				src/command/funct_command_subs.c			\
				src/command/funct_command_subs_bis.c		\
				src/command/funct_command_subs_tree.c		\
				src/command/funct_command_subs_six.c		\
				src/command/funct_command_subs_five.c		\
				src/command/funct_command_send_bis.c		\
				src/command/funct_command_messages.c		\
				src/file_management/channel_save.c			\
				src/file_management/team_save.c				\
				src/file_management/thread_save.c			\
				src/file_management/user_save.c				\

OBJ			=	$(SRC:.c=.o)

NAME		=	../../myteams_server

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
