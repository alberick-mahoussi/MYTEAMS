/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command
*/

#include "my_teams.h"
#include "logging_server.h"

static void to_fill_response_users_one(u_int8_t **param, client_t *client,
                                        buffered_socket_t *bufferedSocket)
{
    bufferedSocket->bufferWrite.usedSize = (to_compt_n(client->username)
    + to_compt_n(client->uuid) + 11);
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    to_check_realloc(bufferedSocket->bufferWrite.octets);
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "USERS\n");
}

static void to_fill_response_users_two(u_int8_t **param, client_t *client,
                                        buffered_socket_t *bufferedSocket)
{
    bufferedSocket->bufferWrite.usedSize +=
    (to_compt_n(client->username) + 1) + (to_compt_n(client->uuid) + 1) + 3;
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    to_check_realloc(bufferedSocket->bufferWrite.octets);
}

static void to_fill_response_users(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket, int i)
{
    if (i == 0) {
        to_fill_response_users_one(param, &server->client[i], bufferedSocket);
    } else {
        to_fill_response_users_two(param, &server->client[i], bufferedSocket);
    }
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets,
    server->client[i].uuid);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets,
    server->client[i].username);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
}

void funct_users(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket)
{
    u_int8_t *users;
    client_t *client = to_check_client_use(server, bufferedSocket);

    for (int i = 0; i < server->nbrClient; i++) {
        to_fill_response_users(param, server, bufferedSocket, i);
        if (server->client[i].login == true) {
            bufferedSocket->bufferWrite.octets =
            strcat(bufferedSocket->bufferWrite.octets, "1");
        } else {
            bufferedSocket->bufferWrite.octets =
            strcat(bufferedSocket->bufferWrite.octets, "0");
        }
        bufferedSocket->bufferWrite.octets =
        strcat(bufferedSocket->bufferWrite.octets, "\n");
    }
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\0");
    write(client->sockConnect->sockfd, bufferedSocket->bufferWrite.octets,
    to_compt_n(bufferedSocket->bufferWrite.octets) + 1);
}
