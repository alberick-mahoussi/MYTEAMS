/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** to_check_command
*/

#include "my_teams.h"

static u_int8_t **to_setup_command(buffer_t *buffer)
{
    u_int8_t *finishCommand;
    u_int8_t **command;

    finishCommand = to_read(buffer);
    command = str_to_word_array(finishCommand, '\n');
    return command;
}

static int is_valid_opt(teams_t const *arg, size_t i,
            server_t *server, buffered_socket_t *bufferedSocket)
{
    if (strcmp((const char *)server->command[0], arg->comd) == 0) {
        COMMAND_GESTION[i].handler(server->command, server, bufferedSocket);
        bufferedSocket->bufferRead.used = true;
        return 1;
    }
    return 0;
}

static void to_check_command_exist(u_int8_t **command,
        buffered_socket_t *bufferedSocket, server_t *server)
{
    int value = 0;

    for (size_t i = 0; i < ARRAY_SIZE(COMMAND_GESTION); i++) {
        if (value != 1) {
            value = is_valid_opt(&COMMAND_GESTION[i], i,
            server, bufferedSocket);
        }
    }
    if (value == 0) {
        printf("500 Unknow command.\r\n");
    }
}

void to_verification_command(buffered_socket_t *bufferedSocket,
                fd_set *set, client_t *client, server_t *server)
{
    server->command = to_setup_command(&bufferedSocket->bufferRead);

    to_check_command_exist(server->command, bufferedSocket, server);
}
