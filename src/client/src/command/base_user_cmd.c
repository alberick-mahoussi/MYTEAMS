/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** base_user_cmd
*/

#include "client.h"
#include "logging_client.h"

int compt_size(u_int8_t *response)
{
    int size = 0;

    for (; response[size]; size++);
    return size;
}

void client_create_response_login(client_t *client)
{
    client->response = realloc(client->response,
    (((compt_size(client->perso.ip) + 1) +
    (compt_size(client->perso.username) + 1)
    + (compt_size(client->uuid) + 1) + 6) * sizeof(u_int8_t)));
    client->response[0] = '\0';
    client->response = strcat(client->response, "LOGIN\n");
    client->response = strcat(client->response, client->perso.ip);
    client->response = strcat(client->response, "\n");
    client->response = strcat(client->response, client->perso.username);
    client->response = strcat(client->response, "\n");
    client->response = strcat(client->response, client->uuid);
    client->response = strcat(client->response, "\0");
}

bool to_check_arg(u_int8_t *command)
{
    int compt = 0;

    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '"') {
            compt++;
        }
    }
    if (compt == 2) {
        return true;
    }
    return false;
}

u_int8_t *clear_username_client(u_int8_t *username)
{
    u_int8_t *tmpUsername = malloc(strlen(username) * sizeof(u_int8_t));
    int j = 0;
    int i = 0;

    if (tmpUsername == NULL) {
        return NULL;
    }
    while (username[i] != '\0') {
        if (username[i] == '"') {
            i++;
        } else {
            tmpUsername[j] = username[i];
            j++;
            i++;
        }
    }
    tmpUsername[j] = '\0';
    return tmpUsername;
}

void funct_login(client_t *client, u_int8_t **command)
{
    uuid_t uuid;
    char uuid_[37];

    if (client->perso.isConnected == true ||
    strlen_2d(command) != 2 || to_check_arg(command[1]) == false) {
        return;
    }
    client->perso.username = strdup(clear_username_client(command[1]));
    client->perso.isConnected = true;
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_);
    client->uuid = strdup(uuid_);
    client_create_response_login(client);
    to_create_response(client);
}
