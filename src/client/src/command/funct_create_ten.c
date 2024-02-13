/*
** EPITECH PROJECT, 2023
** *
** File description:
** funct_create_quatre
*/

#include "client.h"
#include "logging_client.h"

bool to_check_arg_create(u_int8_t **command)
{
    if (strlen_2d(command) != 3) {
        fprintf(stdout, "This is not supported");
        return false;
    } else if (strlen(command[1]) > MAX_NAME_LENGTH ||
        strlen(command[2]) > MAX_DESCRIPTION_LENGTH) {
        fprintf(stdout, "Too long description or name");
        return false;
    }
    return true;
}

void create_team_server(u_int8_t **command,
                u_int8_t *uuid_, client_t *client)
{
    client->response = realloc(client->response,
    (((compt_size(clear_username_client(command[1])) + 1)
    + (compt_size(clear_username_client(command[2]))) +
    (compt_size(uuid_) + 1) + 6) *
    sizeof(u_int8_t)));
    client->response[0] = '\0';
    client->response = strcat(client->response, "TEAM\n");
    client->response =
    strcat(client->response, clear_username_client(command[1]));
    client->response = strcat(client->response, "\n");
    client->response =
    strcat(client->response, clear_username_client(command[2]));
    client->response = strcat(client->response, "\n");
    client->response = strcat(client->response, uuid_);
    client->response = strcat(client->response, "\0");
    to_create_response(client);
}

void create_team_chanel(u_int8_t **command,
                u_int8_t *uuid_, client_t *client, u_int8_t *uuid_team)
{
    client->response = realloc(client->response,
    ((compt_size(clear_username_client(command[1])) + 1) +
    (compt_size(clear_username_client(command[2])) + 1) +
    (compt_size(uuid_team) + 1) + (compt_size(uuid_) + 1) + 7) *
    sizeof(u_int8_t));
    client->response[0] = '\0';
    client->response = strcat(client->response, "CHANEL\n");
    client->response = strcat(client->response, uuid_team);
    client->response = strcat(client->response, "\n");
    client->response =
    strcat(client->response, clear_username_client(command[1]));
    client->response = strcat(client->response, "\n");
    client->response =
    strcat(client->response, clear_username_client(command[2]));
    client->response = strcat(client->response, "\n");
    client->response = strcat(client->response, uuid_);
    client->response = strcat(client->response, "\0");
    to_create_response(client);
}
