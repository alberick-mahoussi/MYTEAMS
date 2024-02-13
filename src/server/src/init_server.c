/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** init_server
*/

#include "my_teams.h"

void init_server(server_t *server, int port)
{
    server->nbrConnectionBufferSocket = 0;
    server->bufferedSocket = NULL;
    server->nbrClient = 0;
    server->client = NULL;
    server->team = NULL;
    server->nbrTeam = 0;
    to_connection_sock_t(&server->callBackSock, port);
    if (bind(server->callBackSock.sockfd, (struct sockaddr *)
    (&server->callBackSock.addr),
    sizeof(server->callBackSock.addr)) < 0)
        return;
    if (listen(server->callBackSock.sockfd, 2) < 0)
        return;
}
