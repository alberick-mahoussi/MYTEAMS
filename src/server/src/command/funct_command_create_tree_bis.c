/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_create_tree_bis
*/

#include "my_teams.h"
#include "logging_server.h"

bool to_check_thread_bis(client_t *client, int *tmpNbr,
                    bool tmp, u_int8_t *uuid_)
{
    if (strcmp(uuid_, client->team[tmpNbr[0]].chanel[tmpNbr[1]].uuid_) == 0) {
        client->position.team = tmpNbr[0];
        client->position.chanel = tmpNbr[1];
        tmp = true;
    }
    return tmp;
}

bool to_check_thread(client_t *client, u_int8_t *uuid_)
{
    bool tmp = false;
    int *tmpNbr = malloc(sizeof(int) * 3);

    for (tmpNbr[0] = 0; tmpNbr[0] < client->nbrTeam; tmpNbr[0]++) {
        for (tmpNbr[1] = 0; tmpNbr[1] <
        client->team[tmpNbr[0]].nbrChanel; tmpNbr[1]++) {
            tmp = to_check_thread_bis(client, tmpNbr, tmp, uuid_);
        }
    }
    return tmp;
}

bool to_check_thread_server_bis(server_t *server, int *tmpNbr,
                    bool tmp, u_int8_t *uuid_)
{
    if (strcmp(uuid_, server->team[tmpNbr[0]].chanel[tmpNbr[1]].uuid_) == 0) {
        server->position.team = tmpNbr[0];
        server->position.chanel = tmpNbr[1];
        tmp = true;
    }
    return tmp;
}
