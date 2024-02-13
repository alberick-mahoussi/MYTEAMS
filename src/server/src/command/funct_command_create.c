/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_create
*/

#include "my_teams.h"
#include "logging_server.h"

void funct_chanel_bis(u_int8_t **param, chanel_t *chanel_client,
                buffered_socket_t *bufferedSocket, chanel_t *chanel)
{
    chanel->usernameChanel = strdup(param[2]);
    chanel->descriptionChanel = strdup(param[3]);
    chanel->uuid_ = strdup(param[4]);
    chanel_client->usernameChanel = strdup(param[2]);
    chanel_client->descriptionChanel = strdup(param[3]);
    chanel_client->uuid_ = strdup(param[4]);
    server_event_channel_created(param[1], param[4], param[2]);
    save_channel(param[4], param[3], param[2]);
}

void funct_chanel(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket)
{
    client_t *client = to_check_client_use(server, bufferedSocket);
    chanel_t *chanel;
    chanel_t *chanel_client;

    if (to_check_chanel(server, param[1]) == false ||
    to_check_chanel_client(client, param[1]) == false) {
        return;
    }
    chanel_client =
    init_new_chanel(&server->team[server->position.team].chanel,
    server->team[server->position.team].nbrChanel);
    chanel = init_new_chanel(&client->team[client->position.team].chanel,
    client->team[client->position.team].nbrChanel);
    funct_chanel_bis(param, chanel_client, bufferedSocket, chanel);
    funct_reponse_chanel_create(bufferedSocket, param, server, client);
    free(bufferedSocket->bufferRead.octets);
    bufferedSocket->bufferRead.octets = NULL;
    bufferedSocket->bufferRead.usedSize = 0;
}

bool to_check_reply(u_int8_t *uuidTeam, server_t *server)
{
    bool tmp = false;
    check_t *tmpNbr = malloc(sizeof(check_t));
    tmpNbr->a = 0;
    tmpNbr->b = 0;
    tmpNbr->c = 0;

    for (tmpNbr->a = 0; tmpNbr->a < server->nbrTeam; tmpNbr->a++) {
        for (tmpNbr->b = 0; tmpNbr->b < server->team[tmpNbr->a].
            nbrChanel; tmpNbr->b++) {
            tmp = to_check_reply_bis(server, tmpNbr, tmp, uuidTeam);
        }
    }
    return tmp;
}

bool to_check_reply_client_bis(client_t *server, check_t *tmpNbr, bool tmp,
                        u_int8_t *uuidTeam)
{
    for (tmpNbr->c = 0; tmpNbr->c < server->team[tmpNbr->a].
            chanel[tmpNbr->b].nbrThread; tmpNbr->c++) {
        if (strcmp(server->team[tmpNbr->a].chanel[tmpNbr->b].
            thread[tmpNbr->c].uuid_, uuidTeam) == 0) {
            tmp = true;
            server->position.team = tmpNbr->a;
            server->position.chanel = tmpNbr->b;
            server->position.thread = tmpNbr->c;
        }
    }
    return tmp;
}

bool to_check_reply_client(u_int8_t *uuidTeam, client_t *server)
{
    bool tmp = false;
    check_t *tmpNbr = malloc(sizeof(check_t));
    tmpNbr->a = 0;
    tmpNbr->b = 0;
    tmpNbr->c = 0;

    for (tmpNbr->a = 0; tmpNbr->a < server->nbrTeam; tmpNbr->a++) {
        for (tmpNbr->b = 0; tmpNbr->b < server->team[tmpNbr->a].
            nbrChanel; tmpNbr->b++) {
            tmp = to_check_reply_client_bis(server, tmpNbr, tmp, uuidTeam);
        }
    }
    return tmp;
}
