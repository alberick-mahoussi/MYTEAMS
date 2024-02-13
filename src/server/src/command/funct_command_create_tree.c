/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_create_tree
*/

#include "my_teams.h"
#include "logging_server.h"

bool to_check_thread_server(server_t *server, u_int8_t *uuid_)
{
    bool tmp = false;
    int *tmpNbr = malloc(sizeof(int) * 3);

    for (tmpNbr[0] = 0; tmpNbr[0] < server->nbrTeam; tmpNbr[0]++) {
        for (tmpNbr[1] = 0; tmpNbr[1] <
        server->team[tmpNbr[0]].nbrChanel; tmpNbr[1]++) {
            tmp = to_check_thread_server_bis(server, tmpNbr, tmp, uuid_);
        }
    }
    return tmp;
}

thread_t *init_new_thread(thread_t **thread, size_t size)
{
    (*thread) = realloc((*thread), (size + 1) * sizeof(thread_t));
    (*thread)[size].msg = NULL;
    (*thread)[size].uuid_ = NULL;
    (*thread)[size].titleThread = NULL;
    (*thread)[size].descriptionThread = NULL;
    (*thread)[size].nbrMessage = 0;
    (*thread)[size].time = 0;
    return thread[size];
}

void funct_thread_bis(u_int8_t **param, client_t *client,
                buffered_socket_t *bufferedSocket, thread_t *thread)
{
    long tmps = atol(param[5]);

    thread->titleThread = strdup(param[2]);
    thread->descriptionThread = strdup(param[3]);
    thread->uuid_ = strdup(param[4]);
    thread->time = tmps;
    thread->uuid_use = strdup(client->uuid);
    client->team[client->position.team].chanel
    [client->position.chanel].nbrThread += 1;
    server_event_thread_created(param[1], param[4], client->uuid,
    param[2], param[3]);
}

void funct_thread_bis_bis(u_int8_t **param, server_t *server, client_t *client)
{
    thread_t *threadS;
    long tmps = atol(param[5]);

    threadS = init_new_thread(&server->team
    [server->position.team].chanel[server->position.chanel].thread,
    server->team[server->position.team].chanel[server->position.chanel]
    .nbrThread);
    threadS->titleThread = strdup(param[2]);
    threadS->descriptionThread = strdup(param[3]);
    threadS->uuid_ = strdup(param[4]);
    threadS->uuid_use = strdup(client->uuid);
    threadS->time = tmps;
    server->team[server->position.team].chanel
    [server->position.chanel].nbrThread += 1;
}

void funct_thread(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket)
{
    client_t *client = to_check_client_use(server, bufferedSocket);
    thread_t *thread;

    to_check_thread(client, param[1]);
    to_check_thread_server(server, param[1]);
    thread = init_new_thread(&client->team
    [client->position.team].chanel[client->position.chanel].thread,
    client->team[client->position.team].chanel[client->position.chanel]
    .nbrThread);
    funct_thread_bis(param, client, bufferedSocket, thread);
    funct_thread_bis_bis(param, server, client);
    funct_reponse_thread_create(bufferedSocket, param, client, server);
    free(bufferedSocket->bufferRead.octets);
    bufferedSocket->bufferRead.octets = NULL;
    bufferedSocket->bufferRead.usedSize = 0;
    save_thread(param[4], param[3], param[2]);
}
