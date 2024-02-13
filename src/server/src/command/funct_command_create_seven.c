/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_create_seven
*/

#include "my_teams.h"
#include "logging_server.h"

void funct_reponse_reply_create_bis(buffered_socket_t *bufferedSocket,
                                u_int8_t **param, client_t *client,
                                server_t *server)
{
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param[1]);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, client->uuid);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param[2]);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\0");
    for (int i = 0; i < server->nbrClient; i++) {
        if (server->client[i].login == true) {
            write(server->client[i].sockConnect->sockfd,
            bufferedSocket->bufferWrite.octets,
            bufferedSocket->bufferWrite.usedSize);
        }
    }
}

void funct_reponse_reply_create(buffered_socket_t *bufferedSocket,
                                u_int8_t **param, client_t *client,
                                server_t *server)
{
    bufferedSocket->bufferWrite.usedSize = ((to_compt_n(param[3]) + 1) +
    (to_compt_n(param[1]) + 1) + (to_compt_n(client->uuid) + 1) +
    (to_compt_n(param[2]) + 1) + 6);
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    to_check_realloc(bufferedSocket->bufferWrite.octets);
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "REPLY\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param[3]);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    funct_reponse_reply_create_bis(bufferedSocket, param, client, server);
    free(bufferedSocket->bufferRead.octets);
    bufferedSocket->bufferRead.octets = NULL;
    bufferedSocket->bufferRead.usedSize = 0;
}

message_t *init_new_msg(message_t **msg, size_t size)
{
    (*msg) = realloc((*msg), (size + 1) * sizeof(message_t));
    (*msg)[size].msg = NULL;
    (*msg)[size].uuid_ = NULL;
    (*msg)[size].uuid_use = NULL;
    return msg[size];
}

void funct_msg_bis(client_t *client, u_int8_t **param,
                    message_t *msg_server, message_t *msg)
{
    long tmps = atol(param[4]);

    msg->msg = strdup(param[2]);
    msg->uuid_use = strdup(client->uuid);
    msg->time = tmps;
    msg_server->msg = strdup(param[2]);
    msg_server->time = tmps;
    msg_server->uuid_use = strdup(client->uuid);
    client->team[client->position.team].chanel[client->position.chanel].
    thread[client->position.thread].nbrMessage += 1;
    server_event_reply_created(param[1], client->uuid, param[2]);
}

void funct_msg(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket)
{
    client_t *client = to_check_client_use(server, bufferedSocket);
    message_t *msg;
    message_t *msg_server;

    to_check_reply(param[1], server);
    to_check_reply_client(param[1], client);
    msg_server = init_new_msg(&server->team[server->position.team]
    .chanel[server->position.chanel].thread[server->position.thread].msg,
    server->team[server->position.team].chanel[server->position.chanel].thread
    [server->position.thread].nbrMessage);
    msg = init_new_msg(&client->team[client->position.team]
    .chanel[client->position.chanel].thread[client->position.thread].msg,
    client->team[client->position.team].chanel[client->position.chanel].thread
    [client->position.thread].nbrMessage);
    funct_msg_bis(client, param, msg_server, msg);
    funct_reponse_reply_create(bufferedSocket, param, client, server);
}
