/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** to_action_on_fd
*/

#include "my_teams.h"

int to_init_fd_set(fd_set *set, server_t *server)
{
    FD_ZERO(set);
    FD_SET(server->callBackSock.sockfd, set);
    for (size_t i = 0; i < server->nbrConnectionBufferSocket; ++i) {
        FD_SET(server->bufferedSocket[i]->sock.sockfd, set);
    }
    if (select(FD_SETSIZE, set, NULL, NULL, NULL) == -1) {
        free_struct(server);
        return -1;
    }
    return 0;
}

static void to_check_error_new_fd(int fd)
{
    if (fd < 0) {
        perror("error new_fd");
    }
}

static void to_check_malloc_error(void *buffer)
{
    if (buffer == NULL) {
        perror("error realloc/malloc on fonction to_connection_fd_set");
    }
}

static void to_connection_fd_set_bis(server_t *server, int new_fd)
{
    to_check_malloc_error(server->bufferedSocket
    [server->nbrConnectionBufferSocket]);
    to_connection_new_buffered_socket(new_fd,
    server->bufferedSocket[server->nbrConnectionBufferSocket],
    &server->callBackSock);
    server->nbrConnectionBufferSocket += 1;
}

int to_connection_fd_set(fd_set *set, server_t *server)
{
    int new_fd = 0;
    socklen_t len = 0;

    len = sizeof(server->callBackSock.addr);
    if (FD_ISSET(server->callBackSock.sockfd, set)) {
        new_fd = accept(server->callBackSock.sockfd,
        (struct sockaddr *)(&server->callBackSock.addr), &len);
        to_check_error_new_fd(new_fd);
        server->bufferedSocket = realloc(server->bufferedSocket,
        (server->nbrConnectionBufferSocket + 1) *
        sizeof(buffered_socket_t *));
        to_check_malloc_error(server->bufferedSocket);
        server->bufferedSocket[server->nbrConnectionBufferSocket] =
        malloc(sizeof(buffered_socket_t) * 1);
        to_connection_fd_set_bis(server, new_fd);
    }
    return 0;
}
