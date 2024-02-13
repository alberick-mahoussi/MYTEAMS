/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_send
*/

#include "my_teams.h"
#include "logging_server.h"

void funct_send_bis_bis(size_t tmp_bis, msg_t *conv, u_int8_t **param)
{
    long tmps = atol(param[3]);

    tmp_bis = nb_ligne(conv->msg_body) + 1;
    conv->msg_body = realloc(conv->msg_body,
    tmp_bis * sizeof(u_int8_t *));
    to_check_realloc_struct_client(conv->msg_body);
    conv->time_sent = realloc(conv->time_sent,
    tmp_bis * sizeof(time_t));
    to_check_realloc_struct_client(conv->time_sent);
    conv->time_sent[tmp_bis - 1] = tmps;
    conv->msg_body[tmp_bis - 1] = strdup(param[2]);
    conv->nbrMsg += 1;
}

bool funct_send_bis(u_int8_t **param, server_t *server, int i, bool status)
{
    size_t tmp = 0;

    for (int y = 0; y < server->client[i].nbrConv; y++) {
        if (server->client[i].conv[y].uuid_sender == param[1]) {
            funct_send_bis_bis(tmp, &server->client[i].conv[y], param);
            status = true;
        }
    }
    return status;
}

void funct_send_tree(bool status, client_t *client,
                client_t *client_bis, u_int8_t **param)
{
    int tmp = 0;

    if (status == false) {
        tmp = client->nbrConv + 1;
        client->conv = realloc(client->conv, tmp * sizeof(msg_t));
        client->conv[tmp - 1].uuid_sender = strdup(param[1]);
        client->conv[tmp - 1].msg_body = malloc(sizeof(u_int8_t *));
        client->conv[tmp - 1].time_sent = malloc(sizeof(time_t));
        client->conv[tmp - 1].time_sent[tmp - 1] = atol(param[3]);
        client->conv[tmp - 1].msg_body[0] = strdup(param[2]);
        client->conv[tmp - 1].nbrMsg = 1;
        tmp = client_bis->nbrConv + 1;
        client_bis->conv = realloc(client_bis->conv, tmp * sizeof(msg_t));
        client_bis->conv[tmp - 1].uuid_sender = strdup(param[1]);
        client_bis->conv[tmp - 1].msg_body = malloc(sizeof(u_int8_t *));
        client_bis->conv[tmp - 1].time_sent = malloc(sizeof(time_t));
        client_bis->conv[tmp - 1].time_sent[0] = atol(param[3]);
        client_bis->conv[tmp - 1].msg_body[0] = strdup(param[2]);
        client_bis->conv[tmp - 1].nbrMsg = 1;
    }
}

void funct_send_four(client_t *client, buffered_socket_t *bufferedSocket,
                    client_t *client_send, u_int8_t **param)
{
    client->nbrConv += 1;
    bufferedSocket->bufferWrite.usedSize +=
    (to_compt_n(client->uuid) + 1 + to_compt_n(param[2]) + 1);
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    to_check_realloc(bufferedSocket->bufferWrite.octets);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, client->uuid);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param[2]);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\0");
    write(client_send->sockConnect->sockfd,
    bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize);
}

void funct_send(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket)
{
    bool status = false;
    size_t tmp = 0;
    client_t *client = to_check_client_use(server, bufferedSocket);

    init_funct_send(bufferedSocket, param);
    for (int i = 0; i < client->nbrConv ; i++) {
        if (strcmp(client->uuid, param[1]) == 0) {
            status = funct_send_bis(param, server, i, status);
            funct_send_tree(status, &server->client[i],
            client, param);
            funct_send_four(client, bufferedSocket, &server->client[i], param);
            server_event_private_message_sended(client->uuid,
                                            server->client[i].uuid, param[2]);
        }
    }
}
