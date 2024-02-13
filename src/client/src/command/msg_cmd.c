/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** msg_cmd
*/

#include "client.h"

void client_create_response_send(client_t *client,
                            u_int8_t **command, time_t tmps)
{
    u_int8_t *tmp = NULL;

    asprintf(&tmp, "%lu", time);
    client->response = realloc(client->response,
    ((compt_size(clear_username_client(command[1]))
    + compt_size(clear_username_client(command[2])) +
    compt_size(tmp) + 8) * sizeof(u_int8_t)));
    client->response = strcpy(client->response, "SEND\n");
    client->response =
    strcat(client->response, clear_username_client(command[1]));
    client->response = strcat(client->response, "\n");
    client->response =
    strcat(client->response, clear_username_client(command[2]));
    client->response = strcat(client->response, "\n");
    client->response = strcat(client->response, tmp);
    client->response = strcat(client->response, "\0");
}

void funct_send(client_t *client, u_int8_t **command)
{
    int i = 0;
    time_t tmps = time(NULL);

    if (strlen_2d(command) != 3 || to_check_arg(command[1]) == false ||
        to_check_arg(command[2]) == false) {
        client_error_unauthorized();
        return;
    }
    if (client->perso.isConnected == true && strlen(command[2]) <=
        MAX_BODY_LENGTH) {
        client_create_response_send(client, command, tmps);
        to_create_response(client);
    } else {
        client_error_unauthorized();
    }
}

void client_create_response_messages(client_t *client, u_int8_t **command)
{
    client->response = realloc(client->response,
    ((compt_size(clear_username_client(command[1])) + 10) * sizeof(u_int8_t)));
    client->response = strcpy(client->response, "MESSAGES\n");
    client->response =
    strcat(client->response, clear_username_client(command[1]));
    client->response = strcat(client->response, "\0");
}

void funct_messages(client_t *client, u_int8_t **command)
{
    if (client->perso.isConnected == true && strlen_2d(command) == 2 &&
        to_check_arg(command[1]) == true) {
        client_create_response_messages(client, command);
        to_create_response(client);
    } else {
        client_error_unauthorized();
    }

}
