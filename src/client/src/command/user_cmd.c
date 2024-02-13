/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** base_user_cmd
*/

#include "client.h"
#include "logging_client.h"

void client_create_response_user(client_t *client, u_int8_t **command)
{
    client->response = realloc(client->response,
    ((compt_size(clear_username_client(command[1])) + 6) * sizeof(u_int8_t)));
    client->response[0] = '\0';
    client->response = strcat(client->response, "USER\n");
    client->response = strcat(client->response,
    clear_username_client(command[1]));
    client->response = strcat(client->response, "\0");
}

void funct_user(client_t *client, u_int8_t **command)
{
    if (client->perso.isConnected == true && strlen_2d(command) == 2 &&
        to_check_arg(command[1]) == true) {
        client_create_response_user(client, command);
        to_create_response(client);
    } else {
        client_error_unauthorized();
    }
}

void client_create_response_logout(client_t *client)
{
    client->response = realloc(client->response,
    ((compt_size(client->uuid) + 8) * sizeof(u_int8_t)));
    client->response[0] = '\0';
    client->response = strcat(client->response, "LOGOUT\n");
    client->response = strcat(client->response, client->uuid);
    client->response = strcat(client->response, "\0");
}

void funct_logout(client_t *client, u_int8_t **command)
{
    if (client->perso.isConnected == true) {
        client->perso.isConnected = false;
        client_create_response_logout(client);
        to_create_response(client);
        client_event_logged_out(client->uuid, client->perso.username);
    } else {
        client_error_unauthorized();
    }
}
