/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** client
*/

#include "my_teams.h"
#include "logging_server.h"

static void to_writte_new_buffered(buffered_socket_t *bufferedSocket,
                                    client_t *client)
{
    bufferedSocket->bufferWrite.usedSize =
    ((to_compt_n(client->username) + 1) +
    (to_compt_n(client->uuid) + 1) + 6);
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    to_check_realloc(bufferedSocket->bufferWrite.octets);
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "LOGIN\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, client->username);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, client->uuid);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\0");
    write(client->sockConnect->sockfd, bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize);
}

static bool to_verifie_client_exist(client_t *client,
                buffered_socket_t *bufferedSocket, size_t nbrClient,
                u_int8_t **param)
{
    for (size_t tmp = 0; tmp < nbrClient; tmp += 1) {
        if (strcmp(client[tmp].username, param[2]) == 0) {
            client[tmp].login = true;
            server_event_user_logged_in(client[tmp].uuid);
            to_writte_new_buffered(bufferedSocket, &client[tmp]);
            return true;
        }
    }
    return false;
}

static void to_init_new_client(client_t *client,
            buffered_socket_t *bufferedSocket, u_int8_t **param)
{
    client->conv = NULL;
    client->buffer.octets = NULL;
    client->buffer.capacity = MAX_LENGTH;
    client->buffer.usedSize = 0;
    client->buffer.finishRead = Start;
    client->sockConnect = &bufferedSocket->sock;
    client->command = NULL;
    client->username = strdup(param[2]);
    client->uuid = strdup(param[3]);
    client->ip = strdup(param[1]);
    client->nbrConv = 0;
    client->nbrTeam = 0;
    client->login = true;
    client->team = NULL;
    client->position.chanel = 0;
    client->position.team = 0;
    client->position.thread = 0;
}

void to_create_new_client(server_t *server, buffered_socket_t *bufferedSocket,
                    u_int8_t **param)
{
    if ((to_verifie_client_exist(server->client, bufferedSocket,
                                server->nbrClient, param)) == true) {
        return;
    }
    server->client = realloc(server->client, (server->nbrClient + 1) *
                            sizeof(client_t));
    if (server->client == NULL) {
        return;
    }
    to_init_new_client(&server->client[server->nbrClient], bufferedSocket,
                    param);
    to_writte_new_buffered(bufferedSocket, &server->client[server->nbrClient]);
    server_event_user_loaded(server->client[server->nbrClient].uuid,
    server->client[server->nbrClient].username);
    save_client(server->client[server->nbrClient].uuid,
    server->client[server->nbrClient].username);
    server_event_user_logged_in(server->client[server->nbrClient].uuid);
    server->nbrClient += 1;
}
