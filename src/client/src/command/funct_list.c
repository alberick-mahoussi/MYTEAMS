/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_list
*/

#include "client.h"

void list_teams(client_t *client, u_int8_t **command)
{
    client->response = realloc(client->response, 11 * sizeof(u_int8_t));
    client->response[0] = '\0';
    client->response = strcat(client->response, "LIST_TEAMS\0");
    to_create_response(client);
}

void list_channel(client_t *client, u_int8_t **command)
{
    client->response = realloc(client->response,
    (compt_size(client->use.team) + 14) * sizeof(u_int8_t));
    client->response[0] = '\0';
    client->response = strcat(client->response, "LIST_CHANEL\n");
    client->response = strcat(client->response, client->use.team);
    client->response = strcat(client->response, "\0");
    to_create_response(client);
}

void list_repply(client_t *client, u_int8_t **command)
{
    client->response = realloc(client->response,
    (compt_size(client->use.team) +
    compt_size(client->use.chanel) +
    compt_size(client->use.thread) + 15) * sizeof(u_int8_t));
    client->response[0] = '\0';
    client->response = strcat(client->response, "LIST_REPLIES\n");
    client->response = strcat(client->response, client->use.team);
    client->response = strcat(client->response, "\n");
    client->response = strcat(client->response, client->use.chanel);
    client->response = strcat(client->response, "\n");
    client->response = strcat(client->response, client->use.thread);
    client->response = strcat(client->response, "\0");
    to_create_response(client);
}

void list_thread(client_t *client, u_int8_t **command)
{
    client->response = realloc(client->response,
    (compt_size(client->use.team) +
    compt_size(client->use.chanel) + 14) * sizeof(u_int8_t));
    client->response[0] = '\0';
    client->response = strcat(client->response, "LIST_THREAD\n");
    client->response = strcat(client->response, client->use.team);
    client->response = strcat(client->response, "\n");
    client->response = strcat(client->response, client->use.chanel);
    client->response = strcat(client->response, "\0");
    to_create_response(client);
}

void funct_list(client_t *client, u_int8_t **command)
{
    switch (client->use.context) {
        case 0:
            list_teams(client, command);
            break;
        case 1:
            list_channel(client, command);
            break;
        case 2:
            list_thread(client, command);
            break;
        case 3:
            list_repply(client, command);
            break;
        default:
            fprintf(stdout, "This is not supported");
            break;
    }
}
