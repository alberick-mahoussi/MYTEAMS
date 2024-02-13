/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_create_bis_bis
*/

#include "my_teams.h"
#include "logging_server.h"

void init_new_team_server(server_t *server)
{
    server->team = realloc(server->team, (server->nbrTeam + 1)
                            * sizeof(team_t));
    server->team[server->nbrTeam].chanel = NULL;
    server->team[server->nbrTeam].uuid_ = NULL;
    server->team[server->nbrTeam].usernameTeam = NULL;
    server->team[server->nbrTeam].descriptionTeam = NULL;
    server->team[server->nbrTeam].nbrChanel = 0;
}

void funct_create_server_team(client_t *client, server_t *server)
{
    init_new_team_server(server);
    server->team[server->nbrTeam].usernameTeam =
    strdup(client->team[client->nbrTeam].usernameTeam);
    server->team[server->nbrTeam].descriptionTeam =
    strdup(client->team[client->nbrTeam].descriptionTeam);
    server->team[server->nbrTeam].uuid_ =
    strdup(client->team[client->nbrTeam].uuid_);
    server->nbrTeam += 1;
    client->nbrTeam += 1;
}
