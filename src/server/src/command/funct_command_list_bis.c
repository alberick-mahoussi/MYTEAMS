/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_list_bis
*/

#include "my_teams.h"
#include "logging_server.h"

thread_t *to_find_thread_tree(client_t *client, u_int8_t *param, int i, int j)
{
    for (int x = 0; x < client->team[i].chanel[j].nbrThread; x++) {
        if (strcmp(param, client->team[i].chanel[j].thread[x].uuid_) == 0) {
            return &client->team[i].chanel[j].thread[x];
        }
    }
    return NULL;
}

thread_t *to_find_thread_bis(client_t *client, u_int8_t *param, int i)
{
    thread_t *thread;

    for (int j = 0; j < client->team[i].nbrChanel; j++) {
        thread = to_find_thread_tree(client, param, i, j);
        if (thread != NULL)
            return thread;
    }
    return NULL;
}

thread_t *to_find_thread(client_t *client, u_int8_t *param)
{
    thread_t *thread;

    for (int i = 0; i < client->nbrTeam; i++) {
        thread = to_find_thread_bis(client, param, i);
        if (thread != NULL)
            return thread;
    }
    return NULL;
}

void funct_list_repply_bis(thread_t *thread, u_int8_t *tmps
                            , buffered_socket_t *bufferedSocket)
{
    for (int i = 0; i < thread->nbrMessage; i++) {
        asprintf(&tmps, "%lu", thread->msg[i].time);
        bufferedSocket->bufferWrite.usedSize +=
        to_compt_n(thread->msg[i].uuid_use) +
        to_compt_n(thread->msg[i].msg) +
        to_compt_n(thread->uuid_) + to_compt_n(tmps) + 5;
        bufferedSocket->bufferWrite.octets =
        realloc(bufferedSocket->bufferWrite.octets,
        bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
        strcat(bufferedSocket->bufferWrite.octets, thread->uuid_);
        strcat(bufferedSocket->bufferWrite.octets, "\n");
        strcat(bufferedSocket->bufferWrite.octets, thread->msg[i].uuid_use);
        strcat(bufferedSocket->bufferWrite.octets, "\n");
        strcat(bufferedSocket->bufferWrite.octets, tmps);
        strcat(bufferedSocket->bufferWrite.octets, "\n");
        strcat(bufferedSocket->bufferWrite.octets, thread->msg[i].msg);
        strcat(bufferedSocket->bufferWrite.octets, "\n");
    }
}

void funct_list_repply(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket)
{
    client_t *client = to_check_client_use(server, bufferedSocket);
    thread_t *thread = to_find_thread(client, param[3]);
    u_int8_t *tmps;

    if (thread == NULL) {
        return;
    }
    bufferedSocket->bufferWrite.usedSize = 14;
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "LIST_REPLIES\n");
    funct_list_repply_bis(thread, tmps, bufferedSocket);
    bufferedSocket->bufferWrite.octets
    [bufferedSocket->bufferWrite.usedSize - 1] = '\0';
    write(client->sockConnect->sockfd, bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize);
}
