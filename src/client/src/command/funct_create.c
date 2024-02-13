/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_create
*/

#include "client.h"
#include "logging_client.h"

void funct_create(client_t *client, u_int8_t **command)
{
    switch (client->use.context) {
        case 0:
            create_teams(command, client->nbrTeam, client);
            break;
        case 1:
            create_channel(command, client);
            break;
        case 2:
            create_thread(command, client);
            break;
        case 3:
            create_reply(command, client);
            break;
        default:
            fprintf(stdout, "This is not supported");
            break;
    }
}
