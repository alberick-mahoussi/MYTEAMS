/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_create_eight
*/

#include "client.h"
#include "logging_client.h"

bool to_find_reply_bis(client_t *client, check_t *tmpNbr, bool tmp)
{
    for (tmpNbr->c = 0; tmpNbr->c < client->team[tmpNbr->a].chanel[tmpNbr->b]
                                                    .nbrThread; tmpNbr->c++) {
        if (strcmp(client->use.thread,
        client->team[tmpNbr->a].chanel[tmpNbr->b]
            .thread[tmpNbr->c].uuid_) == 0) {
            tmp = true;
            client->position.team = tmpNbr->a;
            client->position.chanel = tmpNbr->b;
            client->position.thread = tmpNbr->c;
        }
    }
    return tmp;
}

bool to_find_reply(client_t *client)
{
    bool tmp = false;
    check_t *tmpNbr = malloc(sizeof(check_t));
    tmpNbr->a = 0;
    tmpNbr->b = 0;
    tmpNbr->c = 0;

    for (tmpNbr->a = 0; tmpNbr->a < client->nbrTeam; tmpNbr->a++) {
        for (tmpNbr->b = 0; tmpNbr->b <
        client->team[tmpNbr->a].nbrChanel; tmpNbr->b++) {
            tmp = to_find_reply_bis(client, tmpNbr, tmp);
        }
    }
    return tmp;
}
