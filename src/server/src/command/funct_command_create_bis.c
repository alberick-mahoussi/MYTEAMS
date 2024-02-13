/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_create_bis
*/

#include "my_teams.h"
#include "logging_server.h"

void funct_reponse_team_create_bis(buffered_socket_t *bufferedSocket,
                        u_int8_t **param, server_t *server)
{
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param[3]);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param[1]);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param[2]);
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

void funct_reponse_team_create(buffered_socket_t *bufferedSocket,
                        u_int8_t **param, server_t *server)
{
    bufferedSocket->bufferWrite.usedSize = ((to_compt_n(param[1]) + 1)
    + (to_compt_n(param[2]) + 1) + (to_compt_n(param[3]) + 1) + 5);
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    to_check_realloc(bufferedSocket->bufferWrite.octets);
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "TEAM\n");
    funct_reponse_team_create_bis(bufferedSocket, param, server);
}

void init_new_team(client_t *client)
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

void funct_team(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket)
{
    client_t *client = to_check_client_use(server, bufferedSocket);

    init_new_team(client);
    client->team[client->nbrTeam].usernameTeam = strdup(param[1]);
    client->team[client->nbrTeam].descriptionTeam = strdup(param[2]);
    client->team[client->nbrTeam].uuid_ = strdup(param[3]);
    server_event_team_created(param[3], param[1], client->uuid);
    funct_create_server_team(client, server);
    funct_reponse_team_create(bufferedSocket, param, server);
    free(bufferedSocket->bufferRead.octets);
    bufferedSocket->bufferRead.octets = NULL;
    bufferedSocket->bufferRead.usedSize = 0;
    save_teams(param[3], param[2], param[1]);
}
