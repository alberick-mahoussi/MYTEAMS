/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_response
*/

#include "client.h"

void funct_response_users(client_t *client, u_int8_t **command)
{
    int status;
    int compt = compt_command_subs(command);
    int tmp = 1;

    for (int i = 1; i < compt; i += 3) {
        status = atoi(command[tmp + 2]);
        client_print_users(command[tmp], command[tmp + 1], status);
    }
    free_double_array(command);
    free(client->buffered.bufferRead.octets);
    client->buffered.bufferRead.octets = NULL;
    client->buffered.bufferRead.usedSize = 0;
}

void funct_response_user(client_t *client, u_int8_t **command)
{
    client_print_users(command[1], command[2], atoi(command[3]));
    free_double_array(command);
    free(client->buffered.bufferRead.octets);
    client->buffered.bufferRead.octets = NULL;
    client->buffered.bufferRead.usedSize = 0;
}

void funct_response_send(client_t *client, u_int8_t **command)
{
    int i = 0;
    if (client->perso.isConnected == true && strlen(command[2]) <=
    MAX_BODY_LENGTH) {
        client_event_private_message_received(command[1], command[2]);
    } else {
        client_error_unauthorized();
    }
    free(client->buffered.bufferRead.octets);
    client->buffered.bufferRead.octets = NULL;
    client->buffered.bufferRead.usedSize = 0;
}

long funct_response_messages_bis(int j, int compt, u_int8_t **command, int tmp)
{
    long tmps = 0;

    for (int i = 2; i < tmp; i += 2) {
        if (strcmp(command[j], "TIME") == 0) {
            tmps = atol(command[j + 1]);
            j += 2;
        }
        client_private_message_print_messages(command[1],
        tmps, command[j]);
    }
}

void funct_response_messages(client_t *client, u_int8_t **command)
{
    int j = 2;
    int tmp = compt_command_subs(command);

    if (client->perso.isConnected == true) {
        funct_response_messages_bis(tmp, j, command, tmp);
    } else
        client_error_unauthorized();
    free(client->buffered.bufferRead.octets);
    client->buffered.bufferRead.octets = NULL;
    client->buffered.bufferRead.usedSize = 0;
}
