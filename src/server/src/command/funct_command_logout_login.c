/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_logout_login
*/

#include "my_teams.h"
#include "logging_server.h"

void funct_login(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket)
{
    to_create_new_client(server, bufferedSocket, param);
}

client_t *to_check_client_use(server_t *server,
                buffered_socket_t *bufferedSocket)
{
    for (int i = 0; i < server->nbrClient; i++) {
        if (server->client[i].sockConnect->sockfd ==
        bufferedSocket->sock.sockfd) {
            return &server->client[i];
        }
    }
    return NULL;
}

void funct_logout_bis(buffered_socket_t *bufferedSocket, server_t *server,
                        client_t *client)
{
    for (int i = 0; i < server->nbrClient; i++) {
        if (server->client[i].login == true) {
            write(server->client[i].sockConnect->sockfd,
            bufferedSocket->bufferWrite.octets,
            bufferedSocket->bufferWrite.usedSize);
        }
    }
    server_event_user_logged_out(client->uuid);
    client->login = false;
}

void funct_logout(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket)
{
    client_t *client = to_check_client_use(server, bufferedSocket);

    bufferedSocket->bufferWrite.usedSize = (to_compt_n(client->username)
                                + to_compt_n(client->uuid) + 9);
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    to_check_realloc(bufferedSocket->bufferWrite.octets);
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "LOGOUT\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, client->uuid);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, client->username);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\0");
    funct_logout_bis(bufferedSocket, server, client);
}

void to_check_realloc(u_int8_t *response)
{
    if (response == NULL)
        perror("error realloc");
}
