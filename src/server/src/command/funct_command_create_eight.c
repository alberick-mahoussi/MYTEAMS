/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_create_eight
*/

#include "my_teams.h"
#include "logging_server.h"

bool to_check_reply_bis(server_t *server, check_t *tmpNbr, bool tmp,
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
