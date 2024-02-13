/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_response_tree
*/

#include "client.h"
#include "logging_client.h"

void funct_response_print_teams(client_t *client, u_int8_t **command)
{
    int compt = compt_command_subs(command);

    for (int i = 3; i < compt; i += 3) {
        client_print_teams(command[i - 2], command[i - 1], command[i]);
    }
    free(client->buffered.bufferRead.octets);
    client->buffered.bufferRead.octets = NULL;
    client->buffered.bufferRead.usedSize = 0;
}

void funct_response_print_chanel(client_t *client, u_int8_t **command)
{
    int compt = compt_command_subs(command);

    for (int i = 3; i < compt; i += 3) {
        client_team_print_channels(command[i - 2], command[i - 1], command[i]);
    }
    free(client->buffered.bufferRead.octets);
    client->buffered.bufferRead.octets = NULL;
    client->buffered.bufferRead.usedSize = 0;
}

void funct_response_print_threads(client_t *client, u_int8_t **command)
{
    long tmps = 0;
    int compt = compt_command_subs(command);

    for (int i = 5; i < compt; i += 5) {
        tmps = atol(command[i - 2]);
        client_channel_print_threads(command[i - 4], command[i - 3],
        tmps, command[i - 1], command[i]);
    }
}

void funct_response_print_replies(client_t *client, u_int8_t **command)
{
    long tmps = 0;
    int compt = compt_command_subs(command);

    for (int i = 4; i < compt; i += 4) {
        tmps = atol(command[i - 1]);
        client_thread_print_replies(command[i - 3], command[i - 2],
        tmps, command[i]);
    }
    free(client->buffered.bufferRead.octets);
    client->buffered.bufferRead.octets = NULL;
    client->buffered.bufferRead.usedSize = 0;
}
