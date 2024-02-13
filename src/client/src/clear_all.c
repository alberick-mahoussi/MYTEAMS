/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** clear_all
*/

#include "client.h"

void to_clear(buffer_t *buffer)
{
    free(buffer->octets);
    buffer->usedSize = 0;
}

void free_struct(client_t *client)
{
    free(client->perso.username);
    free(client->uuid);
}

size_t clean_str_bis(size_t i, u_int8_t *command)
{
    for (; command[i] == ' '; i++);
    return i;
}

u_int8_t *to_clean_command(u_int8_t *command)
{
    size_t j = 0;
    u_int8_t *new_command = malloc(sizeof(u_int8_t) *
    (to_compt_n(command) + 1));

    for (size_t i = 0; command[i] != '\0'; i++) {
        if (command[i] == ' ') {
            new_command[j] = ' ';
            i = clean_str_bis(i, command);
            i--;
        } else {
            new_command[j] = command[i];
        }
        j++;
    }
    new_command[j] = '\0';
    return new_command;
}
