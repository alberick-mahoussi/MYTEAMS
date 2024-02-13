/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** to_read_command_input
*/

#include "client.h"

size_t to_compt_n(u_int8_t *command)
{
    size_t n = 0;

    for (; command[n] != '\0'; n++);
    return n;
}

u_int8_t *to_clean_command_input(u_int8_t *command)
{
    size_t j = 0;
    u_int8_t *new_command = malloc(sizeof(u_int8_t) *
    (to_compt_n(command) + 1));

    for (size_t i = 0; command[i] != '\0'; i++) {
        if (command[i] != '\n') {
            new_command[j] = command[i];
            j++;
        }
    }
    new_command[j] = '\0';
    return new_command;
}

u_int8_t **to_setup_command(u_int8_t **command, u_int8_t *tmp_command)
{
    u_int8_t *finishCommand;

    finishCommand = to_read(tmp_command);
    finishCommand = to_clean_command_input(finishCommand);
    command = str_to_word_array_command(finishCommand, ' ');
    return command;
}

void to_read_input(client_t *client, fd_set *set)
{
    u_int8_t **command = NULL;
    u_int8_t *tmp_command = NULL;

    tmp_command = get_command(STDIN_FILENO);
    if (tmp_command == NULL) {
        perror("get_command error");
    }
    command = to_setup_command(command, tmp_command);
    to_check_command_exist(command, client);
    free(tmp_command);
    for (size_t tmp = 0; command[tmp] != NULL; tmp++) {
        free(command[tmp]);
    }
    free(command);
}
