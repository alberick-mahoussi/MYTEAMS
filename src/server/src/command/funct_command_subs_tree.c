/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_subs_tree
*/

#include "my_teams.h"
#include "logging_server.h"

int to_check_team_unsubs(client_t *client, u_int8_t *param)
{
    int i = 0;

    for (i = 0; i < client->nbrTeam; i++) {
        if (strcmp(client->team[i].uuid_, param) == 0) {
            client->team[i].subscribe = false;
            return i;
        }
    }
    return -1;
}

void init_reponse_unkonw_unsubscribe(buffered_socket_t *bufferedSocket,
                            u_int8_t *param, client_t *client)
{
    bufferedSocket->bufferWrite.usedSize = (to_compt_n(param) + 20);
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "UNSUBSCRIBE\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "UNKNOW\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param[1]);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\0");
    write(client->sockConnect->sockfd, bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize);
}

void funct_unsubscribe_bis(u_int8_t **param, buffered_socket_t *bufferedSocket
                            , client_t *client)
{
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param[1]);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\0");
    write(client->sockConnect->sockfd,
    bufferedSocket->bufferWrite.octets, bufferedSocket->bufferWrite.usedSize);
    server_event_user_unsubscribed(param[1], client->uuid);
}

void funct_unsubscribe(u_int8_t **param, server_t *server,
                        buffered_socket_t *bufferedSocket)
{
    client_t *client = to_check_client_use(server, bufferedSocket);
    int i = to_check_team_unsubs(client, param[1]);

    if (i == -1) {
        init_reponse_unkonw_unsubscribe(bufferedSocket, param[1], client);
        return;
    }
    bufferedSocket->bufferWrite.usedSize = (to_compt_n(param[1]) +
    to_compt_n(client->uuid) + 14);
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "UNSUBSCRIBE\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, client->uuid);
    funct_unsubscribe_bis(param, bufferedSocket, client);
}
