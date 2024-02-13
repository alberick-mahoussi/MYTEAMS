/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_create_six
*/

#include "client.h"
#include "logging_client.h"

bool to_find_thread_bis(client_t *client, int i, int j, bool tmp)
{
    if (strcmp(client->use.chanel,
                client->team[i].chanel[j].uuid_) == 0) {
        client->position.team = i;
        client->position.chanel = j;
        tmp = true;
    }
    return tmp;
}

bool to_find_thread(client_t *client)
{
    bool tmp = false;

    for (int i = 0; i < client->nbrTeam; i++) {
        for (int j = 0; j < client->team[i].nbrChanel; j++) {
            tmp = to_find_thread_bis(client, i, j, tmp);
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
    (*thread)[size].time = time(NULL);
    return thread[size];
}

void create_thread_bis(thread_t *thread, client_t *client,
                        u_int8_t **command, u_int8_t *uuid_)
{
    thread->titleThread = strdup(clear_username_client(command[1]));
    thread->descriptionThread = strdup(clear_username_client(command[2]));
    thread->uuid_ = strdup(uuid_);
    client->team[client->position.team].chanel
    [client->position.chanel].nbrThread += 1;
    create_team_thread(command, uuid_, client, thread->time);
}

void create_thread(u_int8_t **command, client_t *client)
{
    uuid_t uuid;
    u_int8_t uuid_[37];
    thread_t *thread;

    if (to_check_arg_create(command) == false ||
    to_find_thread(client) == false ||
    to_check_arg(command[1]) == false || to_check_arg(command[2]) == false) {
        return;
    }
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_);
    thread = init_new_thread(&client->team[client->position.team]
    .chanel[client->position.chanel].thread,
    client->team[client->position.team].chanel[client->position.chanel]
    .nbrThread);
    create_thread_bis(thread, client, command, uuid_);
}
