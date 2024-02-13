/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_subs_bis
*/

#include "my_teams.h"
#include "logging_server.h"

void funct_subscribed_bis_bis(server_t *server, int i,
                    buffered_socket_t *bufferedSocket)
{
    bufferedSocket->bufferWrite.usedSize +=
    (to_compt_n(server->client[i].uuid) +
    to_compt_n(server->client[i].username) + 4);
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, server->client[i].uuid);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, server->client[i].username);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
}

int funct_subscribed_bis(server_t *server, int i,
                    buffered_socket_t *bufferedSocket, u_int8_t **param)
{
    int status = 0;

    if (strcmp(server->client[i].uuid, param[1])) {
        status += 1;
        funct_subscribed_bis_bis(server, i, bufferedSocket);
        if (server->client[i].login == true) {
            bufferedSocket->bufferWrite.octets =
            strcat(bufferedSocket->bufferWrite.octets, "1\n");
        } else {
            bufferedSocket->bufferWrite.octets =
            strcat(bufferedSocket->bufferWrite.octets, "0\n");
        }
    }
    return status;
}

void funct_subscribe_unknow_bis(buffered_socket_t *bufferedSocket,
                                client_t *client)
{
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\0");
    write(client->sockConnect->sockfd, bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize);
}

void funct_subscribe_unknow(int status, buffered_socket_t *bufferedSocket,
                            u_int8_t **param, client_t *client)
{
    if (status == 0) {
        bufferedSocket->bufferWrite.usedSize = (to_compt_n(param) + 8);
        bufferedSocket->bufferWrite.octets =
        realloc(bufferedSocket->bufferWrite.octets,
        bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
        bufferedSocket->bufferWrite.octets[0] = '\0';
        bufferedSocket->bufferWrite.octets =
        strcat(bufferedSocket->bufferWrite.octets, "UNKNOW\n");
        bufferedSocket->bufferWrite.octets =
        strcat(bufferedSocket->bufferWrite.octets, param[1]);
        bufferedSocket->bufferWrite.octets =
        strcat(bufferedSocket->bufferWrite.octets, "\0");
        write(client->sockConnect->sockfd,
        bufferedSocket->bufferWrite.octets,
        bufferedSocket->bufferWrite.usedSize);
        return;
    }
    funct_subscribe_unknow_bis(bufferedSocket, client);
}

void funct_subscribed(u_int8_t **param, server_t *server,
                    buffered_socket_t *bufferedSocket)
{
    client_t *client = to_check_client_use(server, bufferedSocket);
    int status = 0;

    bufferedSocket->bufferWrite.usedSize = 12;
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "SUBSCRIBED\n");
    for (int i = 0; i < server->nbrClient; i++) {
        status = funct_subscribed_bis(server, i, bufferedSocket, param);
    }
    funct_subscribe_unknow(status, bufferedSocket, param, client);
}
