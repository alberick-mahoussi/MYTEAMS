/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** initStructSockT
*/

#include "my_teams.h"

void to_connection_sock_t(sock_t *sock, int port)
{
    sock->addr.sin_addr.s_addr = INADDR_ANY;
    sock->addr.sin_port = htons(port);
    sock->addr.sin_family = AF_INET;
    sock->sockfd = socket(AF_INET, SOCK_STREAM, 0);
}
