/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** *
*/

#include "client.h"
#include "logging_client.h"

static void init_new_team(client_t *client)
{
    client->team = realloc(client->team, (client->nbrTeam + 1) *
    sizeof(team_t));
    client->team[client->nbrTeam].chanel = NULL;
    client->team[client->nbrTeam].uuid_ = NULL;
    client->team[client->nbrTeam].usernameTeam = NULL;
    client->team[client->nbrTeam].descriptionTeam = NULL;
    client->team[client->nbrTeam].nbrChanel = 0;
}

static void create_teams_bis(client_t *client, u_int8_t *uuid_,
                        u_int8_t **command)
{
    client->team[client->nbrTeam].usernameTeam
    = strdup(clear_username_client(command[1]));
    client->team[client->nbrTeam].descriptionTeam =
    strdup(clear_username_client(command[2]));
    client->team[client->nbrTeam].uuid_ = strdup(uuid_);
    client->nbrTeam += 1;
    create_team_server(command, uuid_, client);
}

void create_teams(u_int8_t **command, size_t size, client_t *client)
{
    uuid_t uuid;
    u_int8_t uuid_[37];

    if (to_check_arg_create(command) == false ||
    to_check_arg(command[1]) == false || to_check_arg(command[2]) == false)
        return;
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_);
    init_new_team(client);
    create_teams_bis(client, uuid_, command);
}
