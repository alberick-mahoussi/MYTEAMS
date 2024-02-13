/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** utils_function_bis
*/

#include "client.h"

static void client_init_bis(client_t *client)
{
    client->msg = NULL;
    client->conv = 0;
    client->use.context = 0;
    client->use.thread = NULL;
    client->use.chanel = NULL;
    client->use.team = NULL;
    client->buffered.bufferRead.octets = NULL;
    client->buffered.bufferRead.finishRead = Start;
    client->buffered.bufferRead.usedSize = 0;
    client->buffered.bufferWrite.octets = NULL;
    client->position.team = 0;
    client->position.thread = 0;
    client->position.chanel = 0;
    client->team = NULL;
    client->nbrTeam = 0;
    client->uuid = NULL;
    client->response = NULL;
}

int client_init(client_t *client, char *ip, int port)
{
    client->cControl = 1;
    client->perso.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    client->perso.port = port;
    client->perso.ip = ip;
    client->perso.username = NULL;
    client->perso.isConnected = false;
    client->perso.addr.sin_addr.s_addr = inet_addr(ip);
    client->perso.addr.sin_family = AF_INET;
    client->perso.addr.sin_port = htons(port);
    if (connect(client->perso.sockfd, (struct sockaddr *)
    &client->perso.addr, sizeof(client->perso.addr)) != 0) {
        return -1;
    }
    client_init_bis(client);
    return 0;
}

void init_set(fd_set *set, client_t *client)
{
    FD_ZERO(set);
    FD_SET(STDIN_FILENO, set);
    FD_SET(client->perso.sockfd, set);
}

int compt_command_subs(u_int8_t **command)
{
    int i = 0;

    for (; command[i] != NULL; i++);
    i--;
    return i;
}
