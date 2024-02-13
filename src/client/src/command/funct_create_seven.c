/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_create_seven
*/

#include "client.h"
#include "logging_client.h"

message_t *init_new_msg(message_t **msg, size_t size)
{
    (*msg) = realloc((*msg), (size + 1) * sizeof(message_t));
    (*msg)[size].msg = NULL;
    (*msg)[size].uuid_ = NULL;
    return &(*msg)[size];
}

void create_reply_bis(message_t *msg, u_int8_t **command, client_t *client,
                        u_int8_t *uuid_)
{
    msg->msg = strdup(clear_username_client(command[1]));
    msg->uuid_ = strdup(uuid_);
    client->team[client->position.team].chanel[client->position.chanel].
    thread[client->position.thread].nbrMessage += 1;
    create_team_msg(client, command, client->use.thread);
}

void create_reply(u_int8_t **command, client_t *client)
{
    uuid_t uuid;
    u_int8_t uuid_[37];
    message_t *msg;

    if (to_find_reply(client) == false || strlen_2d(command) != 2 ||
        to_check_arg(command[1]) == false)
        return;
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_);
    msg = init_new_msg(&client->team[client->position.team].chanel
    [client->position.chanel].thread[client->position.thread].msg, client->team
    [client->position.team].chanel[client->position.chanel].thread
    [client->position.thread].nbrMessage);
    create_reply_bis(msg, command, client, uuid_);
}
