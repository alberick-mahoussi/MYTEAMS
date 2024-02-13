/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** to_connect_sock_buffer
*/

#include "my_teams.h"

static void to_connection_buffer_t(buffer_t *buffer)
{
    buffer->capacity = MAX_LENGTH;
    buffer->finishRead = Start;
    buffer->usedSize = 0;
    buffer->octets = NULL;
}

static void to_connection_sock_buffer_t(sock_t *sock, int port, int new_fd)
{
    sock->addr.sin_addr.s_addr = INADDR_ANY;
    sock->addr.sin_port = htons(port);
    sock->addr.sin_family = AF_INET;
    sock->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sock->sockfd = new_fd;
}

void to_connection_new_buffered_socket(int new_fd,
                buffered_socket_t *bufferedSocket, sock_t *sock)
{
    to_connection_sock_buffer_t(&bufferedSocket->sock,
                            sock->addr.sin_port, new_fd);
    to_connection_buffer_t(&bufferedSocket->bufferRead);
    to_connection_buffer_t(&bufferedSocket->bufferWrite);
}
