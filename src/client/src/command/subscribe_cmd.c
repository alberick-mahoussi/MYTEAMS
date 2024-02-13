/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** subscribe_cmd
*/

#include "../../include/client.h"

void funct_subscribe(client_t *client, u_int8_t **command)
{
    if (client->perso.isConnected == true && command[1] != NULL) {
        client->response = realloc(client->response,
        ((compt_size(command[1]) + 11) * sizeof(u_int8_t)));
        client->response[0] = '\0';
        client->response = strcat(client->response, "SUBSCRIBE\n");
        client->response = strcat(client->response,
        clear_username_client(command[1]));
        client->response = strcat(client->response, "\0");
        to_create_response(client);
    } else {
        client_error_unauthorized();
    }
}

void client_create_response_unsubscribe(client_t *client, u_int8_t **command)
{
    client->response = realloc(client->response,
    ((compt_size(command[1]) + 14) * sizeof(u_int8_t)));
    client->response = strcpy(client->response, "UNSUBSCRIBE\n");
    client->response = strcat(client->response,
    clear_username_client(command[1]));
    client->response = strcat(client->response, "\0");
}

void funct_unsubscribe(client_t *client, u_int8_t **command)
{
    if (client->perso.isConnected == true && command[1] != NULL) {
        client_create_response_unsubscribe(client, command);
        to_create_response(client);
    } else {
        client_error_unauthorized();
    }
}

void client_create_response_subscribed(client_t *client, u_int8_t **command)
{
    client->response = realloc(client->response,
    ((compt_size(command[1]) + 13) * sizeof(u_int8_t)));
    client->response = strcpy(client->response, "SUBSCRIBED\n");
    client->response = strcat(client->response,
    clear_username_client(command[1]));
    client->response = strcat(client->response, "\0");
}

void funct_subscribed(client_t *client, u_int8_t **command)
{
    if (client->perso.isConnected == true && command[1] != NULL) {
        client_create_response_subscribed(client, command);
        to_create_response(client);
    } else {
        client_error_unauthorized();
    }
}
