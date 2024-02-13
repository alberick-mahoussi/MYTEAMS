/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_list_tree
*/

#include "my_teams.h"
#include "logging_server.h"

chanel_t *to_find_chanel_bis(int i, client_t *client, u_int8_t *param)
{
    for (int j = 0; j < client->team[i].nbrChanel; j++) {
        if (strcmp(param, client->team[i].chanel[j].uuid_) == 0) {
            return &client->team[i].chanel[j];
        }
    }
    return NULL;
}

chanel_t *to_find_chanel(client_t *client, u_int8_t *param)
{
    chanel_t *chanel;

    for (int i = 0; i < client->nbrTeam; i++) {
        chanel = to_find_chanel_bis(i, client, param);
        if (chanel != NULL) {
            return chanel;
        }
    }
    return NULL;
}

void funct_list_threads_tree(chanel_t *chanel, u_int8_t *tmps, int i
                            , buffered_socket_t *bufferedSocket)
{
    strcat(bufferedSocket->bufferWrite.octets, chanel->thread[i].uuid_);
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    strcat(bufferedSocket->bufferWrite.octets, chanel->thread[i].uuid_use);
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    strcat(bufferedSocket->bufferWrite.octets, tmps);
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    strcat(bufferedSocket->bufferWrite.octets,
    chanel->thread[i].titleThread);
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    strcat(bufferedSocket->bufferWrite.octets,
    chanel->thread[i].descriptionThread);
    strcat(bufferedSocket->bufferWrite.octets, "\n");
}

void funct_list_threads_bis(chanel_t *chanel, u_int8_t *tmps
                            , buffered_socket_t *bufferedSocket)
{
    for (int i = 0; i < chanel->nbrThread; i++) {
        asprintf(&tmps, "%lu", chanel->thread[i].time);
        bufferedSocket->bufferWrite.usedSize +=
        to_compt_n(chanel->thread[i].uuid_) +
        to_compt_n(chanel->thread[i].titleThread) +
        to_compt_n(chanel->thread[i].descriptionThread) + to_compt_n(tmps) +
        to_compt_n(chanel->thread[i].uuid_use) + 5;
        bufferedSocket->bufferWrite.octets =
        realloc(bufferedSocket->bufferWrite.octets,
        bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
        funct_list_threads_tree(chanel, tmps, i, bufferedSocket);
    }
}

void funct_list_threads(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket)
{
    client_t *client = to_check_client_use(server, bufferedSocket);
    chanel_t *chanel = to_find_chanel(client, param[2]);
    u_int8_t *tmps;

    if (chanel == NULL) {
        return;
    }
    bufferedSocket->bufferWrite.usedSize = 13;
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "LIST_THREAD\n");
    funct_list_threads_bis(chanel, tmps, bufferedSocket);
    bufferedSocket->bufferWrite.octets
    [bufferedSocket->bufferWrite.usedSize - 1] = '\0';
    write(client->sockConnect->sockfd, bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize);
}
