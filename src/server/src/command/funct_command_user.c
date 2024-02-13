/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_user
*/

#include "my_teams.h"
#include "logging_server.h"

void funct_user_next(client_t *client, buffered_socket_t *bufferedSocket)
{
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, client->username);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    if (client->login == true) {
        bufferedSocket->bufferWrite.octets =
        strcat(bufferedSocket->bufferWrite.octets, "1");
    } else {
        bufferedSocket->bufferWrite.octets =
        strcat(bufferedSocket->bufferWrite.octets, "0");
    }
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\0");
    write(client->sockConnect->sockfd, bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize);
}

void funct_user(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket)
{
    client_t *client = to_check_client_use(server, bufferedSocket);

    bufferedSocket->bufferWrite.usedSize = to_compt_n(client->username)
    + to_compt_n(client->uuid) + 9;
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    to_check_realloc(bufferedSocket->bufferWrite.octets);
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "USER\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, client->uuid);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    funct_user_next(client, bufferedSocket);
}
