/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_six
*/

#include "my_teams.h"
#include "logging_server.h"

void funct_reponse_chanel_create_bis(buffered_socket_t *bufferedSocket,
                            u_int8_t **param, server_t *server)
{
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
    for (int i = 0; i < server->nbrClient; i++) {
        if (server->client[i].login == true) {
            write(server->client[i].sockConnect->sockfd,
            bufferedSocket->bufferWrite.octets,
            bufferedSocket->bufferWrite.usedSize);
        }
    }
}

void funct_reponse_chanel_create(buffered_socket_t *bufferedSocket,
                            u_int8_t **param, server_t *server,
                            client_t *client)
{
    server->team[server->position.team].nbrChanel += 1;
    client->team[client->position.team].nbrChanel += 1;
    bufferedSocket->bufferWrite.usedSize = ((to_compt_n(param[1]) + 1) +
    (to_compt_n(param[2]) + 1) + (to_compt_n(param[3]) + 1) + 7);
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    to_check_realloc(bufferedSocket->bufferWrite.octets);
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "CHANEL\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param[4]);
    funct_reponse_chanel_create_bis(bufferedSocket, param, server);
}

bool to_check_chanel_client(client_t *client, u_int8_t *param)
{
    for (int i = 0; i < client->nbrTeam; i++) {
        if (strcmp(param, client->team[i].uuid_) == 0) {
            client->position.team = i;
            return true;
        }
    }
}

bool to_check_chanel(server_t *server, u_int8_t *param)
{
    for (int i = 0; i < server->nbrTeam; i++) {
        if (strcmp(param, server->team[i].uuid_) == 0) {
            server->position.team = i;
            return true;
        }
    }
    return false;
}

chanel_t *init_new_chanel(chanel_t **chanel, size_t size)
{
    (*chanel) = realloc(*chanel, (size + 1) * sizeof(chanel_t));
    (*chanel)[size].thread = NULL;
    (*chanel)[size].uuid_ = NULL;
    (*chanel)[size].usernameChanel = NULL;
    (*chanel)[size].descriptionChanel = NULL;
    (*chanel)[size].nbrThread = 0;
    return &(*chanel)[size];
}
