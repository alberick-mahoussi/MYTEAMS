/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_bis
*/

#include "my_teams.h"
#include "logging_server.h"

void funct_messages_tree(buffered_socket_t *bufferedSocket,
                        u_int8_t *msg_body, time_t tmps, u_int8_t *tmp)
{
    asprintf(&tmp, "%lu", tmps);
    bufferedSocket->bufferWrite.usedSize +=
    to_compt_n(msg_body) + to_compt_n(tmp) + 7;
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    to_check_realloc(bufferedSocket->bufferWrite.octets);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "TIME");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, tmp);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, msg_body);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
}

void funct_messages_bis(msg_t *conv, buffered_socket_t *bufferedSocket,
                        u_int8_t **param)
{
    u_int8_t *tmp = NULL;

    if (strcmp(conv->uuid_sender, param[1]) == 0) {
        bufferedSocket->bufferWrite.usedSize +=
        to_compt_n(conv->uuid_sender) + 1;
        bufferedSocket->bufferWrite.octets =
        realloc(bufferedSocket->bufferWrite.octets, sizeof(u_int8_t) *
        bufferedSocket->bufferWrite.usedSize);
        to_check_realloc(bufferedSocket->bufferWrite.octets);
        bufferedSocket->bufferWrite.octets =
        strcat(bufferedSocket->bufferWrite.octets, conv->uuid_sender);
        bufferedSocket->bufferWrite.octets =
        strcat(bufferedSocket->bufferWrite.octets, "\n");
        for (int i = 0; i < conv->nbrMsg; i++) {
            funct_messages_tree(bufferedSocket, conv->msg_body[i],
                                conv->time_sent[i], tmp);
        }
        bufferedSocket->bufferWrite.octets
        [bufferedSocket->bufferWrite.usedSize - 1] = '\0';
    }
}

void funct_messages(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket)
{
    size_t size;
    client_t *client = to_check_client_use(server, bufferedSocket);

    bufferedSocket->bufferWrite.usedSize = to_compt_n(param[0]) + 2;
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    to_check_realloc(bufferedSocket->bufferWrite.octets);
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param[0]);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    for (int y = 0; y < client->nbrConv; y++) {
        funct_messages_bis(&client->conv[y], bufferedSocket, param);
    }
    write(client->sockConnect->sockfd, bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize);
}
