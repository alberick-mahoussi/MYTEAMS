/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_response_bis
*/

#include "client.h"
#include "logging_client.h"

void funct_response_subscribed(client_t *client, u_int8_t **command)
{
    int tmp = 0;
    int compt = compt_command_subs(command);
    int comd = 3;

    if (strcmp(command[1], "UNKNOW") == 0) {
        client_error_unknown_team(command[2]);
        free(client->buffered.bufferRead.octets);
        client->buffered.bufferRead.octets = NULL;
        client->buffered.bufferRead.usedSize = 0;
        return;
    }
    for (int i = 3; i < compt; i += 3) {
        tmp = atoi(command[comd]);
        client_print_user(command[comd - 2], command[comd - 1], tmp);
    }
    free(client->buffered.bufferRead.octets);
    client->buffered.bufferRead.octets = NULL;
    client->buffered.bufferRead.usedSize = 0;
}

void funct_response_unsubscribe(client_t *client, u_int8_t **command)
{
    if (strcmp(command[1], "UNKNOW") == 0) {
        client_error_unknown_team(command[2]);
        free(client->buffered.bufferRead.octets);
        client->buffered.bufferRead.octets = NULL;
        client->buffered.bufferRead.usedSize = 0;
        return;
    }
    if (client->perso.isConnected == true)
        client_print_unsubscribed(command[1], command[2]);
    else
        client_error_unauthorized();
    free(client->buffered.bufferRead.octets);
    client->buffered.bufferRead.octets = NULL;
    client->buffered.bufferRead.usedSize = 0;
}

void funct_response_subscribe(client_t *client, u_int8_t **command)
{
    if (strcmp(command[1], "UNKNOW") == 0) {
        client_error_unknown_team(command[2]);
        free(client->buffered.bufferRead.octets);
        client->buffered.bufferRead.octets = NULL;
        client->buffered.bufferRead.usedSize = 0;
        return;
    }
    if (client->perso.isConnected == true)
        client_print_subscribed(command[1], command[2]);
    else
        client_error_unauthorized();
    free(client->buffered.bufferRead.octets);
    client->buffered.bufferRead.octets = NULL;
    client->buffered.bufferRead.usedSize = 0;
}

void funct_response_login(client_t *client, u_int8_t **command)
{
    if (client->perso.isConnected == true) {
        client_event_logged_in(command[2], command[1]);
    } else {
        client_error_unauthorized();
    }
    free(client->buffered.bufferRead.octets);
    client->buffered.bufferRead.octets = NULL;
    client->buffered.bufferRead.usedSize = 0;
}

void funct_response_logout(client_t *client, u_int8_t **command)
{
    if (client->perso.isConnected == true) {
        client_event_logged_out(command[1], command[2]);
    }
    free(client->buffered.bufferRead.octets);
    client->buffered.bufferRead.octets = NULL;
    client->buffered.bufferRead.usedSize = 0;
}
