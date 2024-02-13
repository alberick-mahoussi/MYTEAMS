/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_create_five
*/

#include "client.h"
#include "logging_client.h"

bool to_find_chanel(client_t *client)
{
    for (int i = 0; i < client->nbrTeam; i++) {
        if (strcmp(client->use.team, client->team[i].uuid_) == 0) {
            client->position.team = i;
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

void create_chanel_bis(chanel_t *chanel, client_t *client,
                    u_int8_t **command, u_int8_t *uuid_)
{
    chanel->usernameChanel = strdup(clear_username_client(command[1]));
    chanel->descriptionChanel = strdup(clear_username_client(command[2]));
    chanel->uuid_ = strdup(uuid_);
    client->team[client->position.team].nbrChanel += 1;
    create_team_chanel(command, uuid_, client, client->use.team);
}

void create_channel(u_int8_t **command, client_t *client)
{
    uuid_t uuid;
    u_int8_t uuid_[37];
    chanel_t *chanel;

    if (to_check_arg_create(command) == false ||
    to_find_chanel(client) == false ||
    to_check_arg(command[1]) == false || to_check_arg(command[2]) == false) {
        return;
    }
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_);
    chanel = init_new_chanel(&client->team[client->position.team].chanel,
    client->team[client->position.team].nbrChanel);
    create_chanel_bis(chanel, client, command, uuid_);
}
