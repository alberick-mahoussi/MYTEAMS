/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** to_read_command_server
*/

#include "client.h"

size_t to_find_command(u_int8_t *command)
{
    size_t n = 0;

    for (; command[n] != '\0'; n++);
    return n;
}

u_int8_t *to_read(u_int8_t *command)
{
    size_t n = to_find_command(command);
    u_int8_t *tmp_command = malloc(sizeof(u_int8_t) * (n + 1));

    if (tmp_command == NULL || n == 0) {
        return NULL;
    }
    memcpy(tmp_command, command, n);
    tmp_command[n] = '\0';
    return tmp_command;
}

u_int8_t **to_setup_command_server(u_int8_t **command, u_int8_t *tmp_command)
{
    u_int8_t *finishCommand;

    finishCommand = to_read(tmp_command);
    command = str_to_word_array(finishCommand, '\n');
    return command;
}

void to_check_finish_read_command(client_t *client, fd_set *set)
{
    u_int8_t **command = NULL;

    if (client->buffered.bufferRead.finishRead == Finish) {
        command = to_setup_command_server(command,
        client->buffered.bufferRead.octets);
        to_check_command_exist(command, client);
    }
}
