/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_use
*/

#include "client.h"
#include "logging_client.h"

void funct_use_bis(int i, client_t *client, u_int8_t **command)
{
    switch (i) {
    case 4:
            client->use.thread = strdup(clear_username_client(command[3]));
    case 3:
            client->use.chanel = strdup(clear_username_client(command[2]));
    case 2:
            client->use.team = strdup(clear_username_client(command[1]));
    case 1:
        client->use.context = i - 1;
        break;
    default:
        dprintf(client->perso.sockfd, "This is not supported");
    }
}

void funct_use(client_t *client, u_int8_t **command)
{
    int i = 0;

    if (client->perso.isConnected == false) {
        dprintf(client->perso.sockfd, "Client is not connected");
        return;
    }
    i = strlen_2d(command);
    for (int tmp = 1; tmp < i; tmp++) {
        if (command[tmp] == NULL || to_check_arg(command[tmp]) == false) {
            dprintf(client->perso.sockfd, "This is not supported");
            return;
        }
    }
    funct_use_bis(i, client, command);
}
