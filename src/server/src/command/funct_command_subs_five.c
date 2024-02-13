/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_subs_five
*/

#include "my_teams.h"
#include "logging_server.h"

bool to_check_team_subs(server_t *server, u_int8_t *param)
{
    for (int i = 0; i < server->nbrTeam; i++) {
        if (strcmp(param, server->team[i].uuid_) == 0) {
            server->position.team = i;
            return true;
        }
    }
    return false;
}

void init_new_team_subs(client_t *client)
{
    client->team = realloc(client->team, (client->nbrTeam + 1)
                            * sizeof(team_t));
    client->team[client->nbrTeam].chanel = NULL;
    client->team[client->nbrTeam].uuid_ = NULL;
    client->team[client->nbrTeam].usernameTeam = NULL;
    client->team[client->nbrTeam].descriptionTeam = NULL;
    client->team[client->nbrTeam].nbrChanel = 0;
    client->team[client->nbrTeam].subscribe = true;
}

chanel_t *init_new_chanel_subs(chanel_t **chanel, size_t size)
{
    (*chanel) = realloc(*chanel, (size + 1) * sizeof(chanel_t));
    (*chanel)[size].thread = NULL;
    (*chanel)[size].uuid_ = NULL;
    (*chanel)[size].usernameChanel = NULL;
    (*chanel)[size].descriptionChanel = NULL;
    (*chanel)[size].nbrThread = 0;
    return &(*chanel)[size];
}

thread_t *init_new_thread_subs(thread_t **thread, size_t size, time_t time)
{
    (*thread) = realloc(*thread, (size + 1) * sizeof(chanel_t));
    (*thread)[size].msg = NULL;
    (*thread)[size].uuid_ = NULL;
    (*thread)[size].titleThread = NULL;
    (*thread)[size].descriptionThread = NULL;
    (*thread)[size].nbrMessage = 0;
    (*thread)[size].time = time;
    return &(*thread)[size];
}

message_t *init_new_msg_subs(message_t **msg, size_t size)
{
    (*msg) = realloc(*msg, (size + 1) * sizeof(chanel_t));
    (*msg)[size].msg = NULL;
    (*msg)[size].uuid_ = NULL;
    return &(*msg)[size];
}
