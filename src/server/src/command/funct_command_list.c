/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_list
*/

#include "my_teams.h"
#include "logging_server.h"

void funct_list_teams_bis(server_t *server,
                buffered_socket_t *bufferedSocket)
{
    for (int i = 0; i < server->nbrTeam; i++) {
        bufferedSocket->bufferWrite.usedSize +=
        to_compt_n(server->team[i].uuid_) +
        to_compt_n(server->team[i].usernameTeam) +
        to_compt_n(server->team[i].descriptionTeam) + 3;
        bufferedSocket->bufferWrite.octets =
        realloc(bufferedSocket->bufferWrite.octets,
        bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
        strcat(bufferedSocket->bufferWrite.octets, server->team[i].uuid_);
        strcat(bufferedSocket->bufferWrite.octets, "\n");
        strcat(bufferedSocket->bufferWrite.octets,
        server->team[i].usernameTeam);
        strcat(bufferedSocket->bufferWrite.octets, "\n");
        strcat(bufferedSocket->bufferWrite.octets,
        server->team[i].descriptionTeam);
        strcat(bufferedSocket->bufferWrite.octets, "\n");
    }
}

void funct_list_teams(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket)
{
    client_t *client = to_check_client_use(server, bufferedSocket);

    bufferedSocket->bufferWrite.usedSize = 12;
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "LIST_TEAMS\n");
    funct_list_teams_bis(server, bufferedSocket);
    bufferedSocket->bufferWrite.octets
    [bufferedSocket->bufferWrite.usedSize - 1] = '\0';
    write(client->sockConnect->sockfd, bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize);
}

team_t *to_find_teams(client_t *client, u_int8_t *param)
{
    for (int i = 0; i < client->nbrTeam; i++) {
        if (strcmp(param, client->team[i].uuid_) == 0) {
            return &client->team[i];
        }
    }
    return NULL;
}

void funct_list_chanel_bis(team_t *team, buffered_socket_t *bufferedSocket)
{
    for (int i = 0; i < team->nbrChanel; i++) {
        bufferedSocket->bufferWrite.usedSize +=
        to_compt_n(team->chanel[i].uuid_) +
        to_compt_n(team->chanel[i].usernameChanel) +
        to_compt_n(team->chanel[i].descriptionChanel) + 3;
        bufferedSocket->bufferWrite.octets =
        realloc(bufferedSocket->bufferWrite.octets,
        bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
        strcat(bufferedSocket->bufferWrite.octets, team->chanel[i].uuid_);
        strcat(bufferedSocket->bufferWrite.octets, "\n");
        strcat(bufferedSocket->bufferWrite.octets,
        team->chanel[i].usernameChanel);
        strcat(bufferedSocket->bufferWrite.octets, "\n");
        strcat(bufferedSocket->bufferWrite.octets,
        team->chanel[i].descriptionChanel);
        strcat(bufferedSocket->bufferWrite.octets, "\n");
    }
}

void funct_list_chanel(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket)
{
    client_t *client = to_check_client_use(server, bufferedSocket);
    team_t *team = to_find_teams(client, param[1]);

    if (team == NULL) {
        return;
    }
    bufferedSocket->bufferWrite.usedSize = 13;
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "LIST_CHANEL\n");
    funct_list_chanel_bis(team, bufferedSocket);
    bufferedSocket->bufferWrite.octets
    [bufferedSocket->bufferWrite.usedSize - 1] = '\0';
    write(client->sockConnect->sockfd, bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize);
}
