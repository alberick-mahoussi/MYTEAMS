/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** user_cmd_bis
*/

#include "client.h"
#include "logging_client.h"

void client_create_response_users(client_t *client)
{
    client->response = realloc(client->response, (6 * sizeof(u_int8_t)));
    client->response[0] = '\0';
    client->response = strcat(client->response, "USERS\0");
}

void funct_users(client_t *client, u_int8_t **command)
{
    if (client->perso.isConnected == true) {
        client_create_response_users(client);
        to_create_response(client);
    } else {
        client_error_unauthorized();
    }
}
