/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_create_bis
*/

#include "client.h"
#include "logging_client.h"

size_t compt_time(u_int8_t *time)
{
    int size = 0;

    for (; time[size] != '\0'; size++);
    return size;
}

void create_team_thread_bis(u_int8_t **command,
                u_int8_t *uuid_, client_t *client, u_int8_t *tmps)
{
    client->response = strcat(client->response, "THREAD\n");
    client->response = strcat(client->response, client->use.chanel);
    client->response = strcat(client->response, "\n");
    client->response =
    strcat(client->response, clear_username_client(command[1]));
    client->response = strcat(client->response, "\n");
    client->response =
    strcat(client->response, clear_username_client(command[2]));
    client->response = strcat(client->response, "\n");
    client->response = strcat(client->response, uuid_);
    client->response = strcat(client->response, "\n");
    client->response = strcat(client->response, tmps);
    client->response = strcat(client->response, "\0");
    to_create_response(client);
}

void create_team_thread(u_int8_t **command,
                u_int8_t *uuid_, client_t *client, time_t time)
{
    u_int8_t *tmps = NULL;

    asprintf(&tmps, "%lu", time);
    client->response = realloc(client->response,
    (((compt_size(clear_username_client(command[1])) + 1) +
    (compt_size(clear_username_client(command[2])) + 1) +
    (compt_size(client->use.chanel) + 1) + (compt_size(uuid_) + 1) +
    (compt_time(tmps) + 1) + 7)
    * sizeof(u_int8_t)));
    client->response[0] = '\0';
    create_team_thread_bis(command, uuid_, client, tmps);
}

void create_team_msg(client_t *client, u_int8_t **command,
                    u_int8_t *uuid_thread)
{
    time_t other = time(NULL);
    u_int8_t *tmps;

    asprintf(&tmps, "%lu", other);
    client->response = realloc(client->response,
    (((compt_size(clear_username_client(command[1])) + 1) +
    (compt_size(uuid_thread) + 1) + (compt_size(tmps) + 1)
    + (compt_size(client->use.team) + 1) + 7) * sizeof(u_int8_t)));
    client->response[0] = '\0';
    client->response = strcat(client->response, "MSG\n");
    client->response = strcat(client->response, uuid_thread);
    client->response = strcat(client->response, "\n");
    client->response =
    strcat(client->response, clear_username_client(command[1]));
    client->response = strcat(client->response, "\n");
    client->response = strcat(client->response, client->use.team);
    client->response = strcat(client->response, "\n");
    client->response = strcat(client->response, tmps);
    client->response = strcat(client->response, "\0");
    to_create_response(client);
}
