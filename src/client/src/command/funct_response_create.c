/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_response_create
*/

#include "client.h"
#include "logging_client.h"

void funct_response_team(client_t *client, u_int8_t **command)
{
    if (client->perso.isConnected == true && strlen_2d(command) == 4) {
        client_event_team_created(command[1], command[2], command[3]);
    } else {
        client_error_unauthorized();
    }
    free(client->buffered.bufferRead.octets);
    client->buffered.bufferRead.octets = NULL;
    client->buffered.bufferRead.usedSize = 0;
}

void funct_response_chanel(client_t *client, u_int8_t **command)
{
    if (client->perso.isConnected == true && strlen_2d(command) == 4) {
        client_event_channel_created(command[1], command[2], command[3]);
    } else {
        client_error_unauthorized();
    }
    free(client->buffered.bufferRead.octets);
    client->buffered.bufferRead.octets = NULL;
    client->buffered.bufferRead.usedSize = 0;
}

void funct_response_thread(client_t *client, u_int8_t **command)
{
    time_t tmps = 0;

    if (client->perso.isConnected == true && strlen_2d(command) == 6) {
        tmps = atol(command[3]);
        client_event_thread_created(command[1], command[2],
        tmps, command[4], command[5]);
    } else {
        client_error_unauthorized();
    }
    free(client->buffered.bufferRead.octets);
    client->buffered.bufferRead.octets = NULL;
    client->buffered.bufferRead.usedSize = 0;
}

void funct_response_msg(client_t *client, u_int8_t **command)
{
    if (client->perso.isConnected == true && strlen_2d(command) == 5) {
        client_event_thread_reply_received(command[1], command[2],
                                        command[3], command[4]);
    } else {
        client_error_unauthorized();
    }
    free(client->buffered.bufferRead.octets);
    client->buffered.bufferRead.octets = NULL;
    client->buffered.bufferRead.usedSize = 0;
}
