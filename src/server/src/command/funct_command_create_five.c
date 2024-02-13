/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_five
*/

#include "my_teams.h"
#include "logging_server.h"

void funct_reponse_thread_create_bis_bis(buffered_socket_t *bufferedSocket,
                            u_int8_t **param)
{
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param[5]);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param[2]);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param[3]);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\0");
}

void funct_reponse_thread_create_bis(buffered_socket_t *bufferedSocket,
                            u_int8_t **param, server_t *server)
{
    funct_reponse_thread_create_bis_bis(bufferedSocket, param);
    for (int i = 0; i < server->nbrClient; i++) {
        if (server->client[i].login == true) {
            write(server->client[i].sockConnect->sockfd,
            bufferedSocket->bufferWrite.octets,
            bufferedSocket->bufferWrite.usedSize);
        }
    }
}

void funct_reponse_thread_create(buffered_socket_t *bufferedSocket,
                            u_int8_t **param, client_t *client,
                            server_t *server)
{
    bufferedSocket->bufferWrite.usedSize = ((to_compt_n(param[2]) + 1) +
    (to_compt_n(client->uuid) + 1) + (to_compt_n(param[3]) + 1) +
    (to_compt_n(param[4]) + 1) + (to_compt_n(param[5]) + 1) + 7);
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    to_check_realloc(bufferedSocket->bufferWrite.octets);
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "THREAD\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param[4]);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, client->uuid);
    funct_reponse_thread_create_bis(bufferedSocket, param, server);
}
